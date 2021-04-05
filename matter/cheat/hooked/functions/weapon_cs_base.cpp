#include "../hooked.h"
#include "../../features/globals.h"

void __fastcall hooked::draw_crosshair( weapon_cs_base* ecx, void* edx ) {

	static auto o_draw_crosshair = m_detour.get< decltype( &draw_crosshair ) >( "C_WeaponCSBase::DrawCrosshair" );

	const auto weapon_info = ecx->get_cs_wpn_data( );
	if ( !weapon_info )
		return;

	if ( m_globals.m_local_player && m_globals.m_local_player->is_scoped( ) )
		return;

	const auto old_weapon_type = weapon_info->m_weapon_type;

	weapon_info->m_weapon_type = 0xff;

	o_draw_crosshair( ecx, edx );

	weapon_info->m_weapon_type = old_weapon_type;

}
