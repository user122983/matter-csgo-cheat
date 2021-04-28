#include "globals.h"

#include "../../valve/interfaces/interfaces.h"
#include "../../valve/shared/in_buttons.h"

void globals::setup( ) {

	m_globals.m_local_player = {

		m_interfaces.m_entity_list->get< cs_player* >( m_interfaces.m_engine->get_local_player( ) ),
		m_globals.m_local_player.pointer->get_player_anim_state_csgo( ),
		m_globals.m_local_player.view_origin,
		m_globals.m_local_player.pointer->get_eye_pos( ),
		m_globals.m_local_player.pointer->get_aim_punch_angle( ),
		m_globals.m_local_player.pointer->get_move_type( ),
		m_globals.m_local_player.pointer->get_flags( ),
		m_globals.m_local_player.pointer->get_team( ),
		
		// recheck this
		m_globals.m_cmd->m_buttons & ( in_forward | in_move_left | in_back | in_move_right | in_jump ),
		
		m_globals.m_local_player.pointer->is_alive( ),
		m_globals.m_local_player.pointer->get_use_new_animstate( ),
		m_globals.m_local_player.pointer->get_spawn_time( )
		
	};

	m_globals.m_weapon.pointer = m_interfaces.m_entity_list->get< weapon_cs_base* >( m_globals.m_local_player.pointer->get_active_weapon( ) );
	
	if ( m_globals.m_weapon.pointer ) {
		
		m_globals.m_weapon = {

			m_globals.m_weapon.pointer,
			m_globals.m_weapon.pointer->get_cs_wpn_data( ),
			m_globals.m_local_player.aim_punch_angle * m_interfaces.m_convar->find_var( xorstr_( "weapon_recoil_scale" ) )->get_float( ),
			m_globals.m_weapon.pointer->get_item_definition_index( ),
			m_globals.m_weapon.pointer->is_gun( ),
			m_globals.m_weapon.is_gun && m_globals.m_cmd->m_buttons & ( in_attack | in_attack2 ),
			m_globals.m_local_player.pointer->is_activity_active( activity_reload )

		};
		
	}

	m_globals.m_game = {

		m_globals.m_game.cs_game_rules_captured,
		m_interfaces.m_cs_game_rules_proxy->is_freeze_period( ),
		m_interfaces.m_cs_game_rules_proxy->is_valve_server( ),
		
	};
	
	m_globals.m_server = {

		m_globals.m_server.send_packet,
		m_interfaces.m_globals->m_interval_per_tick * static_cast< float> ( m_interfaces.m_client_state->m_clockdriftmgr.m_servertick )
		
	};
		
}

void globals::unload( ) {

	m_globals.m_cmd = nullptr;

	m_globals.m_local_player.pointer = nullptr;
	m_globals.m_local_player.anim_state = nullptr;
	
	m_globals.m_weapon.pointer = nullptr;
	m_globals.m_weapon.info = nullptr;

	m_globals.m_game.cs_game_rules_captured = false;
	
}