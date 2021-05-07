#include "legitbot.h"

#include "../../cheat.h"
#include "../../input/input.h"
#include "../../menu/menu.h"

void legitbot::run( ) {
	
	if ( !m_globals.m_local_player.pointer || !m_globals.m_local_player.pointer->is_alive( ) || !m_globals.m_cs_game_rules_captured )
		return;

	if ( m_interfaces.m_cs_game_rules_proxy->is_freeze_period( ) || m_globals.m_local_player.pointer->get_flags( ) & fl_frozen )
		return;
	
	init_settings( );
	
	if ( m_menu.m_legitbot_widgets.m_enabled->get_state( ) ) {

		aimbot( );

		rcs( );
				
		accuracy( );
		
	}

	triggerbot( );
	
	if ( !m_menu.m_antiaim_enabled->get_state( ) )
		return;

	fakelag( );
	
	antiaim( );

}

void legitbot::aimbot( ) {

	if ( !m_menu.m_legitbot_widgets.m_fov->get_value( ) || !m_globals.m_weapon.is_gun )
		return;
	
	find_target( );

	m_player.pointer = m_interfaces.m_entity_list->get< cs_player* >( m_player.index );
	if ( !m_player.pointer || m_player.angle.is_zero( ) )
		return;

	if ( m_menu.m_legitbot_widgets.m_smooth->get_value( ) )
		m_player.angle = m_globals.m_cmd->m_view_angles + ( m_player.angle - m_globals.m_cmd->m_view_angles ) / m_menu.m_legitbot_widgets.m_smooth->get_value( );

	if ( m_menu.m_legitbot_widgets.m_silent_aim->get_state( ) && m_menu.m_legitbot_widgets.m_rcs_enabled->get_state( ) )
		m_player.angle += m_rcs.angle;

	m_player.angle.normalize( );
	m_player.angle.clamp( );

	m_globals.m_cmd->m_view_angles = m_player.angle;

	if ( !m_menu.m_legitbot_widgets.m_silent_aim->get_state( ) )
		m_interfaces.m_engine->set_view_angles( m_player.angle );
	
}

void legitbot::rcs( ) {

	if ( !m_menu.m_legitbot_widgets.m_rcs_enabled->get_state( ) || !m_globals.m_weapon.is_gun )
		return;

	m_rcs.angle = m_globals.m_local_player.punch_angle;

	if ( m_menu.m_legitbot_widgets.m_rcs_x->get_value( ) > 0.f )
		m_rcs.angle.x *= m_menu.m_legitbot_widgets.m_rcs_x->get_value( ) / 100.f;

	if ( m_menu.m_legitbot_widgets.m_rcs_y->get_value( ) > 0.f )
		m_rcs.angle.y *= m_menu.m_legitbot_widgets.m_rcs_y->get_value( ) / 100.f;
		
	if ( !m_menu.m_legitbot_widgets.m_silent_aim->get_state( ) )
		m_interfaces.m_engine->set_view_angles( m_globals.m_cmd->m_view_angles += m_rcs.old_punch_angle - m_rcs.angle );
	else
		m_globals.m_cmd->m_view_angles -= m_rcs.angle;

	m_rcs.old_punch_angle = m_rcs.angle;

}

void legitbot::find_target( ) {

	auto is_visible = [ ]( cs_player* player, const vector_3d end_pos ) {

		ray ray;
		ray.init( m_globals.m_local_player.eye_pos, end_pos );

		trace_filter filter;
		filter.init( m_globals.m_local_player.pointer, 0 );

		game_trace trace;
		m_interfaces.m_engine_trace->trace_ray( ray, mask_shot, &filter, &trace );

		return trace.m_hit_entity == player;

	};
	
	float best_fov = m_menu.m_legitbot_widgets.m_fov->get_value( );
	
	m_cheat.iterate_players( [ this, is_visible, &best_fov ]( cs_player* player ) {

		vector_3d bone_pos;
		player->get_bone_position( 8 - m_menu.m_legitbot_widgets.m_target->get_index( ), bone_pos );

		q_angle angle = m_math.calculate_angle( m_globals.m_local_player.eye_pos, bone_pos ) - m_globals.m_local_player.punch_angle;
		
		float fov = m_math.calculate_fov( m_globals.m_cmd->m_view_angles, angle );

		if ( std::isnan( fov ) || fov < best_fov && is_visible( player, bone_pos ) ) {

			m_player.angle = angle;	
			m_player.index = player->get_client_networkable( )->get_index( );

			best_fov = fov;

		}

	}, m_menu.m_legitbot_widgets.m_friendly_fire->get_state( ) ? iterate_teammates : 0 );
		
}

void legitbot::accuracy( ) {

	if ( !m_menu.m_legitbot_widgets.m_accuracy->get_index( accuracy_faststop ) || !( m_globals.m_local_player.pointer->get_flags( ) & fl_onground ) || m_globals.m_local_player.pointer->get_move_state( ) == 0 )
		return;

	if ( m_globals.m_cmd->m_buttons & ( in_forward | in_move_left | in_back | in_move_right | in_jump ) )
		return;
	
	// hehe
			
}

void legitbot::triggerbot( ) {
	
	if ( !m_menu.m_legitbot_widgets.m_triggerbot_enabled->get_state( ) )
		return;

	q_angle view = m_globals.m_cmd->m_view_angles;
	view += m_globals.m_local_player.punch_angle;

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
	
	m_globals.m_cmd->m_buttons |= in_attack;
	
}

void legitbot::antiaim( ) {
	
	if ( m_globals.m_cmd->m_buttons & in_use || m_globals.m_local_player.pointer->get_move_type( ) == move_type_ladder || m_globals.m_local_player.pointer->get_move_type( ) == move_type_noclip )
		return;
	
	if ( m_globals.m_weapon.info->m_weapon_type == weapon_type_grenade ) {

		base_cs_grenade* grenade = reinterpret_cast< base_cs_grenade* >( m_globals.m_weapon.pointer );
		
		if ( grenade && grenade->get_throw_time( ) > 0.f && ( !grenade->is_pin_pulled( ) || m_globals.m_cmd->m_buttons & ( in_attack | in_attack2 ) ) )
			return;
		
	} else if ( m_globals.m_weapon.info->m_weapon_type == weapon_type_knife ) {
		
		if ( m_globals.m_cmd->m_buttons & in_attack && m_globals.m_weapon.pointer->get_next_primary_attack( ) <= m_globals.m_server_time ||
			m_globals.m_cmd->m_buttons & in_attack2 && m_globals.m_weapon.pointer->get_next_secondary_attack( ) <= m_globals.m_server_time )
			return;
		
	}
		
	static int last_desync_type = desync_none;

	if ( m_menu.m_antiaim_desync->get_index( ) == desync_none ) {

		last_desync_type = desync_none;
		
		return;
		
	}
	
	static float desync_side = 1.f;
	
	if ( GetAsyncKeyState( 0x46 ) )
		desync_side = -desync_side;
	
	auto desync_on_shot = [ ]( ) {

		if ( !m_interfaces.m_client_state->m_choked_commands )
			m_globals.m_cmd->m_buttons &= ~in_attack;
		
	};

	auto micromovement_desync = [ ]( float yaw ) {

		if ( m_globals.m_cmd->m_buttons & ( in_forward | in_move_left | in_back | in_move_right | in_jump ) )
			return;

		float velocity = m_globals.m_local_player.pointer->get_duck_amount( ) ? 3.25f : 1.01f;

		if ( !m_globals.m_cmd->m_forward_move && !m_globals.m_cmd->m_side_move )			
			m_globals.m_cmd->m_side_move = m_globals.m_cmd->m_command_number % 2 ? velocity : -velocity;

		if ( !m_interfaces.m_client_state->m_choked_commands )
			*m_globals.m_send_packet = false;

		if ( !*m_globals.m_send_packet )
			m_globals.m_cmd->m_view_angles.y += yaw * desync_side;

		*m_globals.m_send_packet = m_interfaces.m_client_state->m_choked_commands >= 4;
		
	};
	
	if ( m_menu.m_antiaim_desync->get_index( ) == desync_normal ) {

		desync_on_shot( );
		
		micromovement_desync( 200.f );
		
		last_desync_type = desync_normal;

	} else if ( m_menu.m_antiaim_desync->get_index( ) == desync_extended ) {

		static float spawn_time;

		if ( spawn_time != m_globals.m_local_player.pointer->get_spawn_time( ) || last_desync_type != desync_extended ) {

			spawn_time = m_globals.m_local_player.pointer->get_spawn_time( );

			micromovement_desync( 120.f );

		}
		
		csgo_player_anim_state* anim_state = m_globals.m_local_player.pointer->get_player_anim_state_csgo( );
		if ( !anim_state )
			return;
		
		float lower_body_realign_time = std::fmaxf( 0.f, anim_state->m_lower_body_realign_timer - m_globals.m_server_time );

		if ( lower_body_realign_time < m_interfaces.m_globals->m_interval_per_tick ) {

			desync_on_shot( );

			*m_globals.m_send_packet = false;

			m_globals.m_cmd->m_view_angles.y += 120.f * desync_side;

			*m_globals.m_send_packet = m_interfaces.m_client_state->m_choked_commands >= 4;

		} else {

			desync_on_shot( );

			if ( !m_interfaces.m_client_state->m_choked_commands )
				*m_globals.m_send_packet = false;

			if ( !*m_globals.m_send_packet )
				m_globals.m_cmd->m_view_angles.y -= 120.f * desync_side;
			
			*m_globals.m_send_packet = m_interfaces.m_client_state->m_choked_commands >= 4;

		}

		last_desync_type = desync_extended;

	}
	
}

void legitbot::fakelag() {

	if ( m_menu.m_antiaim_fakelag_type->get_index( ) == fakelag_none || m_menu.m_antiaim_fakelag_triggers->get_index( ) == trigger_none )
		return;

	int fakelag_value = 0;

	if ( m_menu.m_antiaim_fakelag_triggers->get_index( trigger_always ) || (
		m_menu.m_antiaim_fakelag_triggers->get_index( trigger_on_ground ) && m_globals.m_local_player.pointer->get_flags( ) & fl_onground ||
		m_menu.m_antiaim_fakelag_triggers->get_index( trigger_in_air ) && !( m_globals.m_local_player.pointer->get_flags( ) & fl_onground ) ||
		m_menu.m_antiaim_fakelag_triggers->get_index( trigger_on_shot ) && m_globals.m_weapon.is_shooting ||
		m_menu.m_antiaim_fakelag_triggers->get_index( trigger_on_reload ) && m_globals.m_local_player.pointer->is_activity_active( activity_reload ) ) ) {

		fakelag_value = m_menu.m_antiaim_fakelag_value->get_value( );

	}
	
	if ( !fakelag_value )
		return;

	switch ( m_menu.m_antiaim_fakelag_type->get_index( ) ) {
		
		case fakelag_jitter:
			fakelag_value = std::rand( ) % fakelag_value;
			break;
		
		case fakelag_adaptive:
			fakelag_value = fakelag_value * ( m_globals.m_local_player.pointer->get_player_anim_state_csgo( )->m_velocity_length_xy / m_globals.m_weapon.pointer->get_max_speed( ) );
			break;
		
		default: 
			break;
		
	}

	fakelag_value = m_interfaces.m_cs_game_rules_proxy->is_valve_server( ) && fakelag_value > 6 ? std::clamp( fakelag_value, 0, 6 ) : fakelag_value;

	// broken with xorstr
	
	*m_globals.m_send_packet = m_interfaces.m_client_state->m_choked_commands >= fakelag_value;

	if ( m_globals.m_weapon.is_shooting && !m_menu.m_antiaim_fakelag_triggers->get_index( trigger_on_shot ) )
		*m_globals.m_send_packet = true;
	
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
	
	m_menu.m_legitbot_widgets = m_menu.m_weapon_widgets[ weapon ];
	
}