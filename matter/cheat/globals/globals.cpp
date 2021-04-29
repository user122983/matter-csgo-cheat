#include "globals.h"

#include "../../valve/interfaces/interfaces.h"
#include "../../valve/shared/in_buttons.h"

void globals::setup( ) {

	m_globals.m_local_player.pointer = m_interfaces.m_entity_list->get< cs_player* >( m_interfaces.m_engine->get_local_player( ) );
	if ( m_globals.m_local_player.pointer ) {

		m_globals.m_local_player.eye_pos = m_globals.m_local_player.pointer->get_eye_pos( );
		m_globals.m_local_player.pressed_move_key = m_globals.m_cmd->m_buttons & ( in_forward | in_move_left | in_back | in_move_right | in_jump );
		
	}
	
	m_globals.m_weapon.pointer = m_interfaces.m_entity_list->get< weapon_cs_base* >( m_globals.m_local_player.pointer->get_active_weapon( ) );	
	if ( m_globals.m_weapon.pointer ) {
		
		m_globals.m_weapon = {

			m_globals.m_weapon.pointer,
			m_globals.m_weapon.pointer->get_cs_wpn_data( ),
			m_globals.m_local_player.pointer->get_aim_punch_angle( ) * m_interfaces.m_convar->find_var( xorstr_( "weapon_recoil_scale" ) )->get_float( ),
			m_globals.m_weapon.pointer->is_gun( ),
			m_globals.m_weapon.is_gun && m_globals.m_cmd->m_buttons & ( in_attack | in_attack2 ),

		};
		
	}

	m_globals.m_server.time = m_interfaces.m_globals->m_interval_per_tick * static_cast< float > ( m_interfaces.m_client_state->m_clockdriftmgr.m_servertick );
				
}

void globals::unload( ) {

	m_globals.m_cmd = nullptr;

	m_globals.m_local_player.pointer = nullptr;
	
	m_globals.m_weapon.pointer = nullptr;
	m_globals.m_weapon.info = nullptr;

	m_globals.m_game.cs_game_rules_captured = false;
	
}