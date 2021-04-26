#include "../hooked.h"

void __fastcall hooked::weapon_cs_base_fn::draw_crosshair( weapon_cs_base* ecx, void* edx ) {

	static auto o_draw_crosshair = m_modules.m_client_dll.get< decltype( &draw_crosshair ) >( xorstr_( "C_WeaponCSBase::DrawCrosshair" ) );

	cs_weapon_info* weapon_info = ecx->get_cs_wpn_data( );
	if ( !weapon_info )
		return;

	if ( m_globals.m_local_player.pointer && m_globals.m_local_player.pointer->is_scoped( ) )
		return;

	int old_weapon_type = weapon_info->m_weapon_type;

	weapon_info->m_weapon_type = 0xff;

	o_draw_crosshair( ecx, edx );

	weapon_info->m_weapon_type = old_weapon_type;

}
