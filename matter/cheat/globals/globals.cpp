#include "globals.h"

#include "../../valve/shared/in_buttons.h"
#include "../../valve/interfaces/interfaces.h"

void globals::init( ) {

	m_local_player.pointer = m_interfaces.m_entity_list->get< cs_player* >( m_interfaces.m_engine->get_local_player( ) );
	if ( !m_local_player.pointer )
		return;

	static convar* weapon_recoil_scale = m_interfaces.m_convar->find_var( xorstr_( "weapon_recoil_scale" ) );
	
	m_local_player.eye_pos = m_local_player.pointer->get_eye_pos( );
	m_local_player.punch_angle = m_local_player.pointer->get_aim_punch_angle( ) * weapon_recoil_scale->get_float( );
	
	m_weapon.pointer = m_interfaces.m_entity_list->get< weapon_cs_base* >( m_local_player.pointer->get_active_weapon( ) );
	if ( !m_weapon.pointer )
		return;

	m_weapon.info = m_weapon.pointer->get_cs_wpn_data( );
	if ( !m_weapon.info )
		return;

	m_weapon.is_gun = m_weapon.pointer->is_gun( );
	m_weapon.is_shooting = m_weapon.pointer->can_shoot( ) && m_globals.m_cmd->m_buttons & ( in_attack | in_attack2 );

	m_server_time = m_globals.m_local_player.pointer->get_tick_base( ) * m_interfaces.m_globals->m_interval_per_tick;
	
}

