#pragma once

#include "../../other/math/vector_3d.h"

struct color;

struct debug_overlay {

	auto screen_position( vector_3d& point, vector_3d& screen ) {

		return m_memory.get_v_func< int( __thiscall* )( void*, const vector_3d&, vector_3d& ) >( this, 13 )( this, point, screen );

	}

};
