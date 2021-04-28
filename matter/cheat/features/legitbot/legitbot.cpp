#include "legitbot.h"

#include "../../cheat.h"
#include "../../input/input.h"
#include "../../menu/menu.h"

void legitbot::run( ) {
	
	if ( !m_globals.m_local_player.pointer || !m_globals.m_local_player.is_alive || !m_globals.m_game.cs_game_rules_captured )
		return;

	if ( m_globals.m_game.is_freeze_period || m_globals.m_local_player.flags & fl_frozen )
		return;
	
	init_settings( );
	
	if ( m_settings.m_enabled->get_state( ) ) {

		if ( m_globals.m_weapon.is_gun ) {

			aimbot( );

			rcs( );
			
		}
		
		accuracy( );
		
	}

	triggerbot( );
	
	if ( !m_menu.m_antiaim_enabled->get_state( ) )
		return;

	fakelag( );
	
	antiaim( );

}

void legitbot::aimbot( ) {

	if ( !m_settings.m_fov->get_value( ) )
		return;

	// move to cs_player struct
	
	auto is_visible = [ ]( cs_player* player, const vector_3d end_pos ) {

		ray ray;
		ray.init( m_globals.m_local_player.eye_pos, end_pos );

		trace_filter filter;
		filter.init( m_globals.m_local_player.pointer, 0 );

		game_trace trace;
		m_interfaces.m_engine_trace->trace_ray( ray, mask_shot, &filter, &trace );

		return trace.m_hit_entity == player;

	};

	// cleanup these values
	
	q_angle best_angle;
	
	float fov = 0.f, best_fov = FLT_MAX;

	bool player_found = false;
	
	m_cheat.iterate_players( [ this, fov, &best_fov, is_visible, &best_angle, &player_found ]( cs_player* player ) mutable -> void {

		vector_3d bone_pos;
		player->get_bone_position( 8 - m_settings.m_target->get_index( ), bone_pos );
				
		q_angle angle = m_math.calc_angle( m_globals.m_local_player.eye_pos, bone_pos ) - m_globals.m_weapon.punch_angle;
		
		fov = m_math.calc_fov( m_globals.m_cmd->m_view_angles, angle );
		if ( std::isnan( fov ) || fov < best_fov && fov < m_settings.m_fov->get_value( ) && is_visible( player, bone_pos ) ) {
			
			m_player.pointer = player;
			
			player_found = true;
			
			best_fov = fov;
			best_angle = angle;
			
		}
		
	}, m_settings.m_friendly_fire->get_state( ) ? iterate_teammates : 0 );
	
	if ( !player_found )	
		return;
	
	m_player = {

		m_player.pointer,
		m_player.pointer->get_client_networkable( )->get_index( ),

	};
	
	if ( m_settings.m_smooth->get_value( ) )		
		best_angle = m_globals.m_cmd->m_view_angles + ( best_angle - m_globals.m_cmd->m_view_angles ) / m_settings.m_smooth->get_value( );

	if ( m_settings.m_silent_aim->get_state( ) && m_recoil_punch_angle.x )
		best_angle += m_recoil_punch_angle;
	 
	best_angle.normalize( );
	best_angle.clamp( );
	
	m_globals.m_cmd->m_view_angles = best_angle;

	if ( !m_settings.m_silent_aim->get_state( ) )
		m_interfaces.m_engine->set_view_angles( best_angle );
	
}

void legitbot::rcs( ) {

	if ( !m_settings.m_rcs_enabled->get_state( ) || !m_globals.m_local_player.aim_punch_angle.x )
		return;

	m_recoil_punch_angle = m_globals.m_weapon.punch_angle;

	if ( m_settings.m_rcs_x->get_value( ) > 0.f )
		m_recoil_punch_angle.x *= m_settings.m_rcs_x->get_value( ) / 10.f;

	if ( m_settings.m_rcs_y->get_value( ) > 0.f )
		m_recoil_punch_angle.y *= m_settings.m_rcs_y->get_value( ) / 10.f;
	
	static q_angle old_punch_angle;
	
	if ( !m_settings.m_silent_aim->get_state( ) )
		m_interfaces.m_engine->set_view_angles( m_globals.m_cmd->m_view_angles += old_punch_angle - m_recoil_punch_angle );
	else
		m_globals.m_cmd->m_view_angles -= m_recoil_punch_angle;

	old_punch_angle = m_recoil_punch_angle;
	
}

void legitbot::accuracy( ) {

	if ( !m_settings.m_accuracy->get_index( accuracy_faststop ) || !( m_globals.m_local_player.flags & fl_onground ) || m_globals.m_local_player.pressed_move_key )
		return;
			
	q_angle angle;
	m_mathlib_base.vector_angles( m_globals.m_local_player.anim_state->m_velocity, angle );

	angle.y = m_globals.m_cmd->m_view_angles.y - angle.y;

	vector_3d direction;
	m_mathlib_base.angle_vectors( angle, &direction );
	
	vector_3d stop = direction * -m_globals.m_local_player.anim_state->m_velocity_length_xy;

	m_globals.m_cmd->m_forward_move = stop.x;
	m_globals.m_cmd->m_side_move = stop.y;
			
}

void legitbot::triggerbot( ) {
	
	if ( !m_settings.m_triggerbot_enabled->get_state( ) )
		return;

	q_angle view = m_globals.m_cmd->m_view_angles;
	view += m_globals.m_weapon.punch_angle;

	vector_3d forward;
	m_mathlib_base.angle_vectors( view, &forward );

	vector_3d start = m_globals.m_local_player.eye_pos;
	
	forward *= m_globals.m_weapon.info->m_range;
	vector_3d end = start + forward;

	ray ray;
	ray.init( start, end );
	
	trace_filter filter;
	filter.init( m_globals.m_local_player.pointer, 0 );

	game_trace trace;
	m_interfaces.m_engine_trace->trace_ray( ray, mask_shot, &filter, &trace );

	cs_player* player = trace.m_hit_entity;

	if ( !player )
		return;
	
	if ( m_globals.m_weapon.is_shooting )
		m_globals.m_cmd->m_buttons |= in_attack;
	
}

void legitbot::antiaim( ) {

	if ( m_globals.m_cmd->m_buttons & in_use || m_globals.m_local_player.move_type == move_type_ladder || m_globals.m_local_player.move_type == move_type_noclip )
		return;

	if ( m_globals.m_weapon.info->m_weapon_type == weapon_type_grenade ) {
		
		if ( m_globals.m_weapon.pointer->get_throw_time( ) > 0.f && ( !m_globals.m_weapon.pointer->is_pin_pulled( ) || m_globals.m_cmd->m_buttons & ( in_attack | in_attack2 ) ) )
			return;
		
	} else if ( m_globals.m_weapon.info->m_weapon_type == weapon_type_knife ) {
		
		if ( m_globals.m_cmd->m_buttons & in_attack && m_globals.m_weapon.pointer->get_next_primary_attack( ) <= m_globals.m_server.time ||
			m_globals.m_cmd->m_buttons & in_attack2 && m_globals.m_weapon.pointer->get_next_secondary_attack( ) <= m_globals.m_server.time )
			return;
		
	}
		
	static int m_last_desync_type = 0;

	if ( m_menu.m_antiaim_desync->get_index( ) == desync_none ) {

		m_last_desync_type = desync_none;
		
		return;
		
	}
	
	static float desync_side = 1.f;
	if ( m_input.is_key_toggled( 0x46 ) )
		desync_side = -desync_side;
	
	auto desync_on_shot = [ ]( ) {

		if ( !m_globals.m_weapon.is_shooting )
			return;
		
		m_globals.m_cmd->m_buttons &= ~( in_attack | in_attack2 );
		
	};
	
	auto micromovement_desync = [ desync_on_shot ]( float yaw ) mutable  {

		if ( m_globals.m_local_player.pressed_move_key )
			return;

		static bool move_side = false;
		
		float velocity = m_globals.m_local_player.pointer->get_duck_amount( ) ? 3.25f : 1.01f;

		m_globals.m_cmd->m_side_move = move_side ? velocity : -velocity;

		move_side = !move_side;
		
		if ( !m_interfaces.m_client_state->m_choked_commands )
			*m_globals.m_server.send_packet = m_globals.m_cmd->m_command_number % 2;
		
		if ( !*m_globals.m_server.send_packet ) {

			desync_on_shot( );
			
			m_globals.m_cmd->m_view_angles.y += yaw * desync_side;

		}

	};
	
	if ( m_menu.m_antiaim_desync->get_index( ) == desync_normal ) {

		micromovement_desync( 200.f );

		m_last_desync_type = desync_normal;

	} else if ( m_menu.m_antiaim_desync->get_index( ) == desync_extended ) {

		static float spawn_time;

		if ( spawn_time != m_globals.m_local_player.spawn_time || m_last_desync_type != desync_extended ) {

			spawn_time = m_globals.m_local_player.spawn_time;

			micromovement_desync( 120.f );

		}
		
		if ( m_globals.m_local_player.anim_state->m_velocity_length_xy > 0.1 || std::fabs( m_globals.m_local_player.anim_state->m_velocity_length_z ) > 100.f ) {

			m_lby.next_update = m_globals.m_server.time + 0.22f;
			
		} else if ( m_globals.m_server.time >= m_lby.next_update || m_lby.force_update ) {

			m_lby.force_update = false;
			
			m_lby.next_update = m_globals.m_server.time + 1.1f;

		}
		
		if ( m_lby.next_update - m_globals.m_server.time <= m_interfaces.m_globals->m_interval_per_tick ) {

			*m_globals.m_server.send_packet = false;

			desync_on_shot( );
			
			m_globals.m_cmd->m_view_angles.y += 120.f * desync_side;

			
		} else {

			if ( !m_interfaces.m_client_state->m_choked_commands )
				*m_globals.m_server.send_packet = m_globals.m_cmd->m_command_number % 2;
						
			if ( !*m_globals.m_server.send_packet ) {

				desync_on_shot( );

				m_globals.m_cmd->m_view_angles.y -= 120.f * desync_side;

			}
			
		}

		m_last_desync_type = desync_extended;

	}
	
	m_globals.m_cmd->m_buttons &= ~( in_forward | in_back | in_move_right | in_move_left );

}

void legitbot::fakelag( ) {

	if ( m_menu.m_antiaim_fakelag_type->get_index( ) == fakelag_none )
		return;

	int fakelag_value;
				
	if ( m_menu.m_antiaim_fakelag_triggers->get_index( trigger_on_ground ) && m_globals.m_local_player.flags & fl_onground ||
		m_menu.m_antiaim_fakelag_triggers->get_index( trigger_in_air ) && !( m_globals.m_local_player.flags & fl_onground ) ||
		m_menu.m_antiaim_fakelag_triggers->get_index( trigger_on_shot ) && m_globals.m_weapon.is_shooting ||
		m_menu.m_antiaim_fakelag_triggers->get_index( trigger_on_reload ) && m_globals.m_weapon.is_reloading ) {

		fakelag_value = static_cast< int >( m_menu.m_antiaim_fakelag_triggers_value->get_value( ) );

	} else {

		fakelag_value = static_cast< int >( m_menu.m_antiaim_fakelag_value->get_value( ) );
		
	}	
	
	if ( !fakelag_value || m_globals.m_weapon.is_shooting )
		return;

	switch ( m_menu.m_antiaim_fakelag_type->get_index( ) ) {
		
		case fakelag_jitter:
			fakelag_value = std::rand( ) % fakelag_value;
			break;
		
		case fakelag_adaptive:
			fakelag_value = fakelag_value * ( m_globals.m_local_player.anim_state->m_velocity_length_xy / m_globals.m_weapon.pointer->get_max_speed( ) );
			break;
		
		default: 
			break;
		
	}

	fakelag_value = m_globals.m_game.is_valve_server && fakelag_value > 6 ? std::clamp( fakelag_value, 0, 6 ) : fakelag_value;
	*m_globals.m_server.send_packet = m_interfaces.m_client_state->m_choked_commands >= fakelag_value;
	
}

void legitbot::init_settings( ) {

	int weapon = weapon_default;
	
	switch ( m_globals.m_weapon.info->m_weapon_type ) {
		
		case weapon_type_rifle:
			if ( m_globals.m_weapon.info->m_weapon_type == weapon_id_ssg08 && m_menu.m_weapon_widgets[ weapon_scout ].m_enabled->get_state( ) )
				weapon = weapon_scout;
			else if ( m_globals.m_weapon.info->m_weapon_type == weapon_id_awp && m_menu.m_weapon_widgets[ weapon_awp ].m_enabled->get_state( ) )
				weapon = weapon_awp;
			else if ( m_menu.m_weapon_widgets[ weapon_rifles ].m_enabled->get_state( ) )
				weapon = weapon_rifles;
			break;

		case weapon_type_pistol:			
			if ( m_menu.m_weapon_widgets[ weapon_pistol ].m_enabled->get_state( ) )
				weapon = weapon_pistol;
			break;

		case weapon_type_shotgun:
		case weapon_type_machinegun:
			if ( m_menu.m_weapon_widgets[ weapon_heavy ].m_enabled->get_state( ) )
				weapon = weapon_heavy;
			break;
		
		default:
			break;
		
	}
	
	m_settings = m_menu.m_weapon_widgets[ weapon ];
	
}