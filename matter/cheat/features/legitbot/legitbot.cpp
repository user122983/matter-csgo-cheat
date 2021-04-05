#include "legitbot.h"

#include "../globals.h"
#include "../../cheat.h"
#include "../../menu/menu.h"

/*  todo:
 *
 *  fix desync with fakelag
 *  
 *  return on grenade throw etc, ladder ...
 *  fakelag and desync cmd tick count % 2 problem fix
 *
 *  maybe: check if lby is the same and micromove (desync swaying when not foucused)
 *  small sway on normal desync when crouched
 *  
 */

void legitbot::run( ) {

	if ( !m_globals.m_local_player || !m_globals.m_local_player->is_alive( ) || m_interfaces.m_cs_game_rules_proxy->is_freeze_period( ) || m_globals.m_local_player->get_flags( ) & ( 1 << 6 ) )
		return;

	m_local_player = {

		m_globals.m_local_player,
		m_globals.m_local_player->get_player_anim_state_csgo( ),
		
	};

	m_weapon.pointer = m_interfaces.m_entity_list->get< weapon_cs_base* >( m_local_player.pointer->get_active_weapon( ) );
	if ( m_weapon.pointer )
		m_weapon.info = m_weapon.pointer->get_cs_wpn_data( );

	if ( !m_menu.m_antiaim_enabled->get_state( ) || m_globals.m_cmd->m_buttons & in_use )
		return;

	fakelag( );

	antiaim( );

}

void legitbot::antiaim( ) const {

	static std::size_t m_last_desync_type;

	if ( m_menu.m_antiaim_desync->get_index( ) == desync_none ) {

		m_last_desync_type = desync_none;
		
		return;
		
	}
	
	auto micromovement_desync = [ ]( const float yaw ) {

		if ( m_globals.m_cmd->m_buttons & ( in_move_left ) || m_globals.m_cmd->m_buttons & ( in_move_right ) )
			return;

		static auto move_side = false;
		
		const auto velocity = m_globals.m_local_player->get_duck_amount( ) ? 3.25f : 1.01f;

		m_globals.m_cmd->m_side_move = move_side ? velocity : -velocity;

		move_side = !move_side;
		
		*m_legitbot.m_send_packet = m_globals.m_cmd->m_command_number % 2;

		if ( !*m_legitbot.m_send_packet )
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

		const auto server_time = m_interfaces.m_globals->m_interval_per_tick * m_interfaces.m_client_state->m_clockdriftmgr.m_servertick;

		static auto m_next_lby_update = -1.f;
		if ( m_local_player.anim_state->m_velocity_length_xy > 0.1 )
			m_next_lby_update = server_time + 0.22f;
		else if ( server_time >= m_next_lby_update || m_next_lby_update == -1.f )
			m_next_lby_update = server_time + 1.1f;

		if ( m_next_lby_update - server_time <= m_interfaces.m_globals->m_interval_per_tick ) {

			m_globals.m_cmd->m_view_angles.y += 120;
			*m_legitbot.m_send_packet = false;

		} else {

			*m_legitbot.m_send_packet = m_globals.m_cmd->m_command_number % 2;

			if ( !*m_legitbot.m_send_packet )
				m_globals.m_cmd->m_view_angles.y -= 120;

		}

		m_last_desync_type = desync_extended;

	}

	m_globals.m_cmd->m_buttons &= ~( in_forward | in_back | in_move_right | in_move_left );

}

void legitbot::fakelag( ) const {

	if ( m_menu.m_antiaim_fakelag_type->get_index( ) == fakelag_none )
		return;

	auto fakelag_value = static_cast< int >( m_menu.m_antiaim_fakelag_value->get_value( ) );

	switch ( m_menu.m_antiaim_fakelag_type->get_index( ) ) {
		case fakelag_jitter:
			fakelag_value = std::rand( ) % fakelag_value;
			break;
		case fakelag_break_lag_comp:
			fakelag_value = fakelag_value * ( m_local_player.anim_state->m_velocity_length_xy / m_weapon.pointer->get_max_speed( ) );
			break;
	}

	fakelag_value = m_interfaces.m_cs_game_rules_proxy->is_valve_server( ) ? std::clamp( fakelag_value, 0, 6 ) : fakelag_value;
	*m_legitbot.m_send_packet = m_interfaces.m_client_state->m_choked_commands >= fakelag_value;
	
}
