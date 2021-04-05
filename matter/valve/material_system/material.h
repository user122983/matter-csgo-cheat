#pragma once

struct material {

	auto set_material_var_flag( const int flag, const bool on ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, int, bool ) >( this, 29 )( this, flag, on );

	}

};