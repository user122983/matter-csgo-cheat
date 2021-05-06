#pragma once

struct material {

	auto set_material_var_flag( int flag, bool on ) {

		return m_memory.get_v_func< void( __thiscall* )( void*, int, bool ) >( this, 29 )( this, flag, on );

	}

};