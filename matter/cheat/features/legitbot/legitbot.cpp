#include "legitbot.h"

#include "../globals.h"
#include "../../menu/menu.h"
#include "../../valve/valve.h"

/*  todo:
 *
 *  return on grenade throw etc, ladder ...
 *
 *  small sway on normal desync when crouched
 *  when switching ANIMATION_LAYER_ADJUST
 *  
 */

void legitbot::run( ) {

	if ( !m_globals.m_local_player || !m_globals.m_local_player->is_alive( ) || !m_globals.m_cs_game_rules_captured || m_interfaces.m_cs_game_rules_proxy->is_freeze_period( ) || m_globals.m_local_player->get_flags( ) & fl_frozen )
		return;

	m_local_player = {

		m_globals.m_local_player,
		m_globals.m_local_player->get_player_anim_state_csgo( ),
		
	};

	m_weapon.pointer = m_interfaces.m_entity_list->get< weapon_cs_base* >( m_local_player.pointer->get_active_weapon( ) );
	if ( m_weapon.pointer )
		m_weapon.info = m_weapon.pointer->get_cs_wpn_data( );

	if ( !m_menu.m_antiaim_enabled->get_state( ) )
		return;

	fakelag( );

	/*	if ( m_weapon.pointer->is_gun( ) ) {

		if ( m_weapon.pointer->can_shoot( ) && ( m_globals.m_cmd->m_buttons & in_attack
			|| m_local_player.pointer->get_item_definition_index( ) == weapon_revolver && m_globals.m_cmd->m_buttons & in_attack2 ) )
			return;

	} else if ( m_weapon.info->m_weapon_type == weapon_type_knife ) {

		if ( ( m_globals.m_cmd->m_buttons & in_attack && m_local_player.pointer->get_next_primary_attack( ) <= m_globals.m_m_globals.m_server_time ) ||
			( m_globals.m_cmd->m_buttons & in_attack2 && m_local_player.pointer->get_next_secondary_attack( ) <= m_globals.m_m_globals.m_server_time ) )
			return;

	} else if ( auto grenade = reinterpret_cast< base_cs_grenade* >( m_local_player.pointer->get_active_weapon( ) ); grenade && m_weapon.info->m_weapon_type == weapon_type_grenade ) {

		if ( !grenade->is_pin_pulled( ) || m_globals.m_cmd->m_buttons & ( in_attack | in_attack2 ) ) {

			if ( grenade->get_throw_time( ) > 0.f )
				return;

		} */
	
	if ( m_globals.m_cmd->m_buttons & in_use ) 
		return;
		
	antiaim( );

}

void legitbot::antiaim( ) const {
	
	static auto m_last_desync_type = 0;

	if ( m_menu.m_antiaim_desync->get_index( ) == desync_none ) {

		m_last_desync_type = desync_none;
		
		return;
		
	}

	const auto is_shooting = m_weapon.pointer->can_shoot( ) && m_globals.m_cmd->m_buttons & in_attack;
	
	auto micromovement_desync = [ is_shooting ]( const float yaw ) {

		if ( m_globals.m_cmd->m_buttons & in_move_left || m_globals.m_cmd->m_buttons & in_move_right )
			return;

		static auto move_side = false;
		
		const auto velocity = m_globals.m_local_player->get_duck_amount( ) ? 3.25f : 1.01f;

		m_globals.m_cmd->m_side_move = move_side ? velocity : -velocity;

		move_side = !move_side;

		if ( is_shooting )
			return;
		
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
		
		if ( spawn_time != m_local_player.pointer->get_spawn_time( ) || m_last_desync_type != desync_extended ) {

			spawn_time = m_local_player.pointer->get_spawn_time( );

			micromovement_desync( 120.f );
			
		}
		
		static auto next_lby_update = -1.f;
		if ( m_local_player.anim_state->m_velocity_length_xy > 0.1 )
			next_lby_update = m_globals.m_server_time + 0.22f;
		else if ( m_globals.m_server_time >= next_lby_update || next_lby_update == -1.f )
			next_lby_update = m_globals.m_server_time + 1.1f;

		if ( next_lby_update - m_globals.m_server_time <= m_interfaces.m_globals->m_interval_per_tick ) {

			*m_globals.m_send_packet = false;

			if ( !is_shooting )
				m_globals.m_cmd->m_view_angles.y += 120;

		} else {

			if ( !m_fakelag_value )
				*m_globals.m_send_packet = m_globals.m_cmd->m_command_number % 2;
	
			if ( !*m_globals.m_send_packet && !is_shooting )
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
