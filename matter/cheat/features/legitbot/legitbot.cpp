#include "legitbot.h"

#include "../globals.h"
#include "../../menu/menu.h"
#include "../../valve/valve.h"

/*  todo:
 *
 *	key binder activation
 *
 *	antiaim:
 *	
 *  return on ladder ...
 *
 *  small sway on normal desync when going crouched
 *  when switching desync type ANIMATION_LAYER_ADJUST (try disabling it)
 *  
 */

void legitbot::run( ) {

	if ( !m_globals.m_local_player || !m_globals.m_local_player->is_alive( ) || !m_globals.m_cs_game_rules_captured || m_interfaces.m_cs_game_rules_proxy->is_freeze_period( ) || m_globals.m_local_player->get_flags( ) & fl_frozen ) {

		m_player.pointer = nullptr;

		return;

	}
	
	m_local_player = {

		m_globals.m_local_player,
		m_globals.m_local_player->get_player_anim_state_csgo( ),
		
	};

	m_weapon.pointer = m_interfaces.m_entity_list->get< weapon_cs_base* >( m_local_player.pointer->get_active_weapon( ) );
	if ( m_weapon.pointer )
		m_weapon.info = m_weapon.pointer->get_cs_wpn_data( );

	m_weapon.item_definition_index = reinterpret_cast< base_combat_character* >( m_weapon.pointer )->get_item_definition_index( );
	m_weapon.is_gun = m_weapon.pointer->is_gun( );
	
	if ( m_menu.m_weapon_widgets[ weapon_default ].m_enabled->get_state( ) ) {
		
		aimbot( );
		
		rcs( );
		
	}
	
	if ( !m_menu.m_antiaim_enabled->get_state( ) )
		return;

	fakelag( );

	// maybe desync on knife?
	
/*	if ( m_weapon.info->m_weapon_type == weapon_type_knife ) {

		if ( ( m_globals.m_cmd->m_buttons & in_attack && m_local_player.pointer->get_next_primary_attack( ) <= m_globals.m_server_time ) ||
			( m_globals.m_cmd->m_buttons & in_attack2 && m_local_player.pointer->get_next_secondary_attack( ) <= m_globals.m_server_time ) ) {

			m_lby.force_update = true;

			return;
			
		}

	}*/

	if ( auto grenade = reinterpret_cast< base_cs_grenade* >( m_weapon.pointer ); grenade && m_weapon.info->m_weapon_type == weapon_type_grenade ) {

		if ( grenade->get_throw_time( ) > 0.f && ( !grenade->is_pin_pulled( ) || m_globals.m_cmd->m_buttons & ( in_attack | in_attack2 ) ) )
			return;
		
	}
	
	if ( m_globals.m_cmd->m_buttons & in_use ) 
		return;
		
	antiaim( );

}

void legitbot::aimbot( ) {

	if ( !m_weapon.is_gun )  {

		m_player.pointer = nullptr;
		
		return;
		
	}
		
	int weapon_id;
	if ( m_menu.m_weapon_widgets[ weapon_scout ].m_enabled->get_state( ) && m_weapon.item_definition_index == weapon_id_ssg08 )
		weapon_id = weapon_scout;
	else if ( m_menu.m_weapon_widgets[ weapon_awp ].m_enabled->get_state( ) && m_weapon.item_definition_index == weapon_id_awp )
		weapon_id = weapon_awp;
	else if ( m_menu.m_weapon_widgets[ weapon_pistol ].m_enabled->get_state( ) && m_weapon.info->m_weapon_type == weapon_type_pistol )
		weapon_id = weapon_pistol;
	else if ( m_menu.m_weapon_widgets[ weapon_heavy ].m_enabled->get_state( ) && m_weapon.info->m_weapon_type == weapon_type_shotgun || m_weapon.info->m_weapon_type == weapon_type_machinegun )
		weapon_id = weapon_heavy;
	else if ( m_menu.m_weapon_widgets[ weapon_rifles ].m_enabled->get_state( ) && m_weapon.info->m_weapon_type == weapon_type_rifle )
		weapon_id = weapon_rifles;
	else
		weapon_id = weapon_default;
	
	m_settings = m_menu.m_weapon_widgets[ weapon_id ];

	if ( !m_settings.m_fov->get_value( ) ) {

		m_player.pointer = nullptr;

		return;

	}

	auto calc_player_angle = [ ]( cs_player* player, q_angle& angle ) {

		// todo: use input from settings for getting aim bone
		
		const auto head_bone = player->lookup_bone( "head_0" );
		if ( !head_bone )
			return;

		vector_3d head_pos;
		player->get_bone_position( head_bone, head_pos );
		 
		angle = m_math.calc_angle( m_legitbot.m_local_player.pointer->get_eye_pos( ), head_pos );
		
	};
	
	auto fov = 0.f, best_fov = FLT_MAX;

	m_cheat.iterate_players( [ this, fov, best_fov, calc_player_angle ]( cs_player* player ) mutable -> void {

		q_angle angle;
		calc_player_angle( player, angle );

		fov = m_math.calc_fov( m_globals.m_cmd->m_view_angles, angle );

		if ( std::isnan( fov ) || fov < best_fov && fov < m_settings.m_fov->get_value( ) ) {

			m_player.pointer = player;
			best_fov = fov;
			
		}	
		
	}, m_settings.m_friendly_fire->get_state( ) ? iterate_teammates : 0 );
	
	if ( !m_player.pointer || !m_player.pointer->is_alive( ) || m_player.pointer->get_client_networkable( )->is_dormant( ) ) {

		m_player.pointer = nullptr;

		return;

	}
	
	m_player = {

		m_player.pointer,
		m_player.pointer->get_client_networkable( )->get_index( ),

	};

	// todo: get values from loop
	
	q_angle angle;
	calc_player_angle( m_player.pointer, angle );

	fov = m_math.calc_fov( m_globals.m_cmd->m_view_angles, angle );
	
	if ( fov > m_settings.m_fov->get_value( ) )  {

		m_player.pointer = nullptr;

		return;
		
	}
	
	if ( m_settings.m_smooth->get_value( ) ) {

		const auto delta = angle - m_globals.m_cmd->m_view_angles;
		angle = m_globals.m_cmd->m_view_angles + delta / m_settings.m_smooth->get_value( );
		
	}

	angle.normalize( );
	angle.clamp( );
	
	m_globals.m_cmd->m_view_angles = angle;

	if ( !m_settings.m_silent_aim->get_state( ) )
		m_interfaces.m_engine->set_view_angles( angle );
	
}

void legitbot::rcs( ) {

	if ( !m_settings.m_rcs_enabled->get_state( ) )
		return;
	
	static q_angle old_punch_angle;
	auto punch_angle = *m_globals.m_local_player->get_aim_punch_angle( ) * 2;

	if ( m_settings.m_rcs_x->get_value( ) )
		punch_angle.x *= m_settings.m_rcs_x->get_value( ) / 10;

	if ( m_settings.m_rcs_y->get_value( ) )
		punch_angle.y *= m_settings.m_rcs_y->get_value( ) / 10;

	if ( *m_globals.m_local_player->get_shots_fired( ) >= 2 )
		m_interfaces.m_engine->set_view_angles( m_globals.m_cmd->m_view_angles += old_punch_angle - punch_angle );

	old_punch_angle = punch_angle;
}

void legitbot::antiaim( ) {
	
	static auto m_last_desync_type = 0;

	if ( m_menu.m_antiaim_desync->get_index( ) == desync_none ) {

		m_last_desync_type = desync_none;
		
		return;
		
	}

	const auto is_shooting = m_weapon.is_gun && m_weapon.pointer->can_shoot( ) && m_globals.m_cmd->m_buttons & in_attack;
	
	auto micromovement_desync = [ ]( const float yaw ) {

		if ( m_globals.m_cmd->m_buttons & in_move_left || m_globals.m_cmd->m_buttons & in_move_right )
			return;

		static auto move_side = false;
		
		const auto velocity = m_globals.m_local_player->get_duck_amount( ) ? 3.25f : 1.01f;

		m_globals.m_cmd->m_side_move = move_side ? velocity : -velocity;

		move_side = !move_side;
		
		if ( !m_legitbot.m_fakelag_value )
			*m_globals.m_send_packet = m_globals.m_cmd->m_command_number % 2;
		
		if ( !*m_globals.m_send_packet )
			m_globals.m_cmd->m_view_angles.y += yaw;

	};

	if ( m_menu.m_antiaim_desync->get_index( ) == desync_normal ) {

		micromovement_desync( 200.f );

		m_last_desync_type = desync_normal;

	} else if ( m_menu.m_antiaim_desync->get_index( ) == desync_extended ) {

		static float spawn_time;
		
		if ( spawn_time != m_local_player.pointer->get_spawn_time( ) || m_last_desync_type != desync_extended || m_lby.force_update ) {
			
			spawn_time = m_local_player.pointer->get_spawn_time( );

			m_lby.force_update = false;
			
			micromovement_desync( 120.f );
			
		}
		
		if ( m_local_player.anim_state->m_velocity_length_xy > 0.1 )
			m_lby.next_update = m_globals.m_server_time + 0.22f;
		else if ( m_globals.m_server_time >= m_lby.next_update || !m_lby.next_update )
			m_lby.next_update = m_globals.m_server_time + 1.1f;
		
		if ( m_lby.next_update - m_globals.m_server_time <= m_interfaces.m_globals->m_interval_per_tick ) {

			*m_globals.m_send_packet = false;

			m_globals.m_cmd->m_view_angles.y += 120;

		} else {
			
			if ( !m_fakelag_value || is_shooting )
				*m_globals.m_send_packet = m_globals.m_cmd->m_command_number % 2;
	
			if ( !*m_globals.m_send_packet )
				m_globals.m_cmd->m_view_angles.y -= 120;

		}

		m_last_desync_type = desync_extended;

	}

	m_globals.m_cmd->m_buttons &= ~( in_forward | in_back | in_move_right | in_move_left );

}

void legitbot::fakelag( ) {
	
	if ( m_menu.m_antiaim_fakelag_type->get_index( ) == fakelag_none ) {

		m_fakelag_value = 0;
		
		return;
		
	}

	// think how to make this cleaner / readable
	
	if ( m_menu.m_antiaim_fakelag_triggers->get_index( trigger_on_ground ) && m_local_player.pointer->get_flags( ) & fl_onground ||
		m_menu.m_antiaim_fakelag_triggers->get_index( trigger_in_air ) && !( m_local_player.pointer->get_flags() & fl_onground ) ||
		m_menu.m_antiaim_fakelag_triggers->get_index( trigger_on_shot ) && *m_local_player.pointer->get_shots_fired( ) > 0 ||
		m_menu.m_antiaim_fakelag_triggers->get_index( trigger_on_reload ) && m_local_player.pointer->is_activity_active( activity_reload ) ) {

		m_fakelag_value = static_cast< int >( m_menu.m_antiaim_fakelag_triggers_value->get_value( ) );

	} else {

		m_fakelag_value = static_cast< int >( m_menu.m_antiaim_fakelag_value->get_value( ) );
		
	}	

	if ( !m_fakelag_value )
		return;

	switch ( m_menu.m_antiaim_fakelag_type->get_index( ) ) {
		case fakelag_jitter:
			m_fakelag_value = std::rand( ) % m_fakelag_value;
			break;
		case fakelag_adaptive:
			m_fakelag_value = m_fakelag_value * ( m_local_player.anim_state->m_velocity_length_xy / m_weapon.pointer->get_max_speed( ) );
			break;
		default: 
			break;
	}
	
	m_fakelag_value = m_interfaces.m_cs_game_rules_proxy->is_valve_server( ) ? std::clamp( m_fakelag_value, 0, 6 ) : m_fakelag_value;
	*m_globals.m_send_packet = m_interfaces.m_client_state->m_choked_commands >= m_fakelag_value;
	
}
