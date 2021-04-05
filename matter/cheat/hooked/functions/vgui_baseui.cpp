#include "../hooked.h"

#include "../../menu/menu.h"
#include "../../features/visuals/visuals.h"
#include "../../features/globals.h"

void __fastcall hooked::paint( engine_vgui* ecx, void* edx, const paint_mode mode ) {

	static auto o_paint = m_detour.get< decltype( &paint ) >( "CEngineVGui::Paint" );

	// capture cs_game_rules once per game
	
	if ( !m_interfaces.m_engine->is_in_game( ) )
		m_globals.m_cs_game_rules_captured = false;
	
	if ( m_interfaces.m_engine->is_in_game( ) && !m_globals.m_cs_game_rules_captured ) {

		m_globals.m_cs_game_rules_captured = true;

		m_interfaces.m_cs_game_rules_proxy = **reinterpret_cast< cs_game_rules_proxy*** >( m_signatures.m_client_dll.find_pattern( "A1 ? ? ? ? 85 C0 0F 84 ? ? ? ? 80 B8 ? ? ? ? ? 74 7A" ) + 0x1 );
		
	}
	
	if ( ecx->m_static_transition_panel && ( mode & paint_uipanels ) ) {

		m_interfaces.m_surface->start_drawing( );

		m_visuals.run( );

		m_menu.m_menu->render( );

		m_interfaces.m_surface->finish_drawing( );

	}

	return o_paint( ecx, edx, mode );

}
