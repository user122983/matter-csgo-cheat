#include "../hooked.h"

#include <intrin.h>

bool __fastcall hooked::client_mode_shared_fn::create_move( void* ecx, void* edx, float input_sample_time, user_cmd* cmd ) {

	static auto o_create_move = m_modules.m_client_dll.get< decltype( &create_move ) >( xorstr_( "ClientModeShared::CreateMove" ) );
	
	m_globals.m_cmd = cmd;
	
	if ( !cmd || !cmd->m_command_number )
		return o_create_move( ecx, edx, input_sample_time, cmd );

	m_globals.init( );

	stack stack( _AddressOfReturnAddress( ) );
	m_globals.m_send_packet = stack.next( ).local( 0x1c ).as< bool* >( );

	q_angle old_view_angles = m_globals.m_cmd->m_view_angles;
	
	m_legitbot.run( );
	
	m_misc.movement_fix( old_view_angles );
	
	m_globals.m_cmd->m_view_angles.normalize( );
	m_globals.m_cmd->m_view_angles.clamp( );
	
	return false;

}

float __fastcall hooked::client_mode_shared_fn::get_view_model_fov( void* ecx, void* edx ) {

	return m_menu.m_fov->get_value( );

}

void __fastcall hooked::client_mode_shared_fn::override_view( void* ecx, int edx, view_setup* view_setup ) {

	static auto o_override_view = m_modules.m_client_dll.get< decltype( &override_view ) >( xorstr_( "ClientModeShared::OverrideView" ) );

	m_globals.m_local_player.view_origin = view_setup->m_origin;

	o_override_view( ecx, edx, view_setup );
	
} 