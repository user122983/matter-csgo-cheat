#include "../hooked.h"

#include "../../menu/menu.h"
#include "../../features/globals.h"
#include "../../features/legitbot/legitbot.h"
#include "../../features/misc/misc.h"

#include <intrin.h>

bool __fastcall hooked::create_move( void* ecx, void* edx, const float input_sample_time, user_cmd* cmd ) {

	static auto o_create_move = m_detour.get< decltype( &create_move ) >( "ClientModeShared::CreateMove" );
	
	m_globals.m_local_player = m_interfaces.m_entity_list->get< cs_player* >( m_interfaces.m_engine->get_local_player( ) );
	
	if ( !cmd || !cmd->m_command_number )
		return o_create_move( ecx, edx, input_sample_time, cmd );
	
	m_globals.m_cmd = cmd;
	
	const stack stack( _AddressOfReturnAddress( ) );

	m_globals.m_send_packet = stack.next( ).local( 0x1c ).as< bool* >( );
	
	auto old_view_angles = m_globals.m_cmd->m_view_angles;
	
	m_legitbot.run( );
	
	m_misc.movement_fix( old_view_angles );
	
	return false;

}

float __fastcall hooked::get_view_model_fov( void* ecx, void* edx ) {

	return m_menu.m_fov->get_value( );

}

void __fastcall hooked::override_view( void* ecx, const int edx, view_setup* view_setup ) {

	static auto o_override_view = m_detour.get< decltype( &override_view ) >( "ClientModeShared::OverrideView" );

	m_globals.m_view_origin = view_setup->m_origin;

	o_override_view( ecx, edx, view_setup );
	
}