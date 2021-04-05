#include "cheat.h"

#include "features/globals.h"
#include "hooked/hooked.h"
#include "input/input.h"
#include "render/render.h"
#include "menu/menu.h"

DWORD WINAPI cheat::setup( void* parameter ) {

	const auto handle = static_cast< HMODULE >( parameter );

	m_console.setup( "cheat.club" );

	while ( !( m_matter.m_window = FindWindowA( "Valve001", nullptr ) ) )
		m_utils.sleep( 100 );

	if ( !m_pe.setup( ) || !m_signatures.setup( ) || !m_interfaces.setup( ) || !m_netvars.setup( )  || !m_input.setup( ) || !m_render.setup( ) || !m_menu.setup( ) || !m_hooked.setup( ) )
		FreeLibraryAndExitThread( handle , EXIT_FAILURE );

	while ( !m_input.is_key_down( VK_DELETE ) )
		m_utils.sleep( 100 );

	FreeLibraryAndExitThread( handle, EXIT_SUCCESS );

}

void cheat::unload( ) {

	m_input.unload( );

	m_hooked.unload( );

	m_console.unload( );

	Beep( 400, 400 );

}

void cheat::iterate_players( const std::function< void( cs_player* ) >& function, const int flags ) {

	if ( !m_globals.m_local_player )
		return;

	for ( auto i = 1; i <= m_interfaces.m_globals->m_max_clients; i++ ) {

		auto player = m_interfaces.m_entity_list->get< cs_player* >( i );
		if ( !player )
			continue;

		if ( !( flags & iterate_dead ) )
			if ( !player->is_alive( ) )
				continue;

		if ( !( flags & iterate_dormant ) )
			if ( player->get_client_networkable( )->is_dormant( ) )
				continue;

		if ( !( flags & iterate_teammates ) )
			if ( player->get_team( ) == m_globals.m_local_player->get_team( ) )
				continue;

		function( player );

	}

}