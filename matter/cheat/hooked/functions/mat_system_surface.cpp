#include "../hooked.h"

#include "../../menu/menu.h"

void __fastcall hooked::lock_cursor( surface* ecx, void* edx ) {

	static auto o_lock_cursor = m_detour.get< decltype( &lock_cursor ) >( "CMatSystemSurface::LockCursor" );

	if ( m_menu.m_menu->get_state( ) ) {

		m_interfaces.m_surface->unlock_cursor( ); 
		m_interfaces.m_input_system->enable_input( false );

		return;
		
	} else {

		m_interfaces.m_input_system->enable_input( true );
		
	}
	
	return o_lock_cursor( ecx, edx );

}
