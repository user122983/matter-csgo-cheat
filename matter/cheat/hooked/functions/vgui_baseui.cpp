#include "../hooked.h"

#include "../../menu/menu.h"
#include "../../features/visuals/visuals.h"
#include "../../features/globals.h"

void __fastcall hooked::vgui_baseui_fn::paint( engine_vgui* ecx, void* edx, const paint_mode mode ) {

	static auto o_paint = m_modules.m_engine_dll.get< decltype( &paint ) >( "CEngineVGui::Paint" );

	// capture cs_game_rules once per game
	
	if ( !m_interfaces.m_engine->is_in_game( ) )
		m_globals.m_cs_game_rules_captured = false;
	
	if ( m_interfaces.m_engine->is_in_game( ) && !m_globals.m_cs_game_rules_captured ) {

		m_globals.m_cs_game_rules_captured = true;

		m_interfaces.m_cs_game_rules_proxy = **m_modules.m_client_dll.get_address( "CCSGameRulesProxy::CGameRulesProxy" ).add( 0x1 ).as< cs_game_rules_proxy*** >( );
		
	}
	
	if ( ecx->m_static_transition_panel && ( mode & paint_uipanels ) ) {

		m_interfaces.m_surface->start_drawing( );

		m_visuals.run( );
		
		m_menu.m_menu->render( );

		m_interfaces.m_surface->finish_drawing( );

	}

	return o_paint( ecx, edx, mode );

}
