#include "../hooked.h"

#include <intrin.h>

bool __fastcall hooked::client_mode_shared_fn::create_move( void* ecx, void* edx, float input_sample_time, user_cmd* cmd ) {

	static auto o_create_move = m_modules.m_client_dll.get< decltype( &create_move ) >( "ClientModeShared::CreateMove" );

	// initialize globals
	
	m_globals.m_local_player.pointer = m_interfaces.m_entity_list->get< cs_player* >( m_interfaces.m_engine->get_local_player( ) );
	m_globals.cmd = cmd;
	
	if ( !cmd || !cmd->m_command_number )
		return o_create_move( ecx, edx, input_sample_time, cmd );

	m_globals.m_local_player.anim_state = m_globals.m_local_player.pointer->get_player_anim_state_csgo( );
	m_globals.m_local_player.pointer->get_player_anim_state_csgo( );

	m_globals.m_weapon.pointer = m_interfaces.m_entity_list->get< weapon_cs_base* >( m_globals.m_local_player.pointer->get_active_weapon( ) );
	
	if ( m_globals.m_weapon.pointer ) {

		m_globals.m_weapon.base_combat_pointer = reinterpret_cast< base_combat_character* >( m_globals.m_weapon.pointer );
		
		m_globals.m_weapon.info = m_globals.m_weapon.pointer->get_cs_wpn_data( );
		m_globals.m_weapon.item_definition_index = m_globals.m_weapon.base_combat_pointer->get_item_definition_index( );
		m_globals.m_weapon.is_gun = m_globals.m_weapon.pointer->is_gun( );
		
	}

	m_globals.m_weapon.recoil_scale = m_interfaces.m_convar->find_var( "weapon_recoil_scale" )->get_float( );
	
	stack stack( _AddressOfReturnAddress( ) );
	
	m_globals.m_server.time = m_interfaces.m_globals->m_interval_per_tick * static_cast< float >( m_interfaces.m_client_state->m_clockdriftmgr.m_servertick );
	m_globals.m_server.send_packet = stack.next( ).local( 0x1c ).as< bool* >( );
	
	q_angle old_view_angles = m_globals.cmd->m_view_angles;

	m_legitbot.run( );
				
	m_misc.movement_fix( old_view_angles );

	m_globals.cmd->m_view_angles.normalize( );
	m_globals.cmd->m_view_angles.clamp( );
	
	return false;

}

float __fastcall hooked::client_mode_shared_fn::get_view_model_fov( void* ecx, void* edx ) {

	return m_menu.m_fov->get_value( );

}

void __fastcall hooked::client_mode_shared_fn::override_view( void* ecx, const int edx, view_setup* view_setup ) {

	static auto o_override_view = m_modules.m_client_dll.get< decltype( &override_view ) >( "ClientModeShared::OverrideView" );

	m_globals.m_local_player.view_origin = view_setup->m_origin;

	o_override_view( ecx, edx, view_setup );
	
} 