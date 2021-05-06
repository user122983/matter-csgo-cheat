#include "cheat.h"

#include "hooked/hooked.h"
#include "input/input.h"
#include "render/render.h"
#include "menu/menu.h"

#include <thread>

DWORD WINAPI cheat::setup( void* parameter ) {

	HMODULE handle = static_cast< HMODULE >( parameter );

	m_console.setup( xorstr_( "cheat" ) );

	while ( !( m_cheat.m_window = FindWindowA( xorstr_( "Valve001" ), nullptr ) ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );

	if ( !m_pe.setup( ) || !m_modules.setup( ) || !m_interfaces.setup( ) || !m_netvars.setup( ) || !m_menu.setup( ) || !m_input.setup( ) || !m_render.setup( ) || !m_hooked.setup( ) )
		FreeLibraryAndExitThread( handle, EXIT_FAILURE );

	while ( !m_input.is_key_down( VK_DELETE ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );

	FreeLibraryAndExitThread( handle, EXIT_SUCCESS );

}

void cheat::unload( ) {

	m_console.unload( );

	m_hooked.unload( );

	m_input.unload( );

}

void cheat::iterate_players( const std::function< void( cs_player* ) >& function, int flags ) {

	for ( int i = 1; i <= m_interfaces.m_globals->m_max_clients; i++ ) {

		cs_player* player = m_interfaces.m_entity_list->get< cs_player* >( i );
		if ( !player )
			continue;

		if ( player == m_globals.m_local_player.pointer )
			continue;
		
		if ( !( flags & iterate_dead ) )
			if ( !player->is_alive( ) )
				continue;

		if ( !( flags & iterate_dormant ) )
			if ( player->get_client_networkable( )->is_dormant( ) )
				continue;

		if ( !( flags & iterate_teammates ) )
			if ( player->get_team( ) == m_globals.m_local_player.pointer->get_team( ) )
				continue;

		function( player );

	}

}