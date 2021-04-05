#include "../hooked.h"

#include "../../features/globals.h"

void __fastcall hooked::level_shutdown( void* ecx, void* edx ) {

	static auto o_level_shutdown = m_detour.get< decltype( &level_shutdown ) >( "CHLClient::LevelShutdown" );

	m_globals.m_local_player = nullptr;

	m_globals.m_cmd = nullptr;

	return o_level_shutdown( ecx, edx );

}
