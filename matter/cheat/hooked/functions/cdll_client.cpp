#include "../hooked.h"

void __fastcall hooked::cdll_client_fn::level_shutdown( void* ecx, void* edx ) {

	static auto o_level_shutdown = m_modules.m_client_dll.get< decltype( &level_shutdown ) >( "CHLClient::LevelShutdown" );

	m_globals.m_local_player.pointer = nullptr;

	m_globals.m_cmd = nullptr;

	m_globals.m_weapon.pointer = nullptr;

	o_level_shutdown( ecx, edx );

}
