#pragma once

#include "../../other/math/vector_3d.h"

struct color;

struct debug_overlay {

	auto screen_position( vector_3d& point, vector_3d& screen ) {

		return m_memory.get_v_func< int( __thiscall* )( void*, const vector_3d&, vector_3d& ) >( this, 13 )( this, point, screen );

	}

	auto draw_box_overlay( const vector_3d& origin, const vector_3d& abs_min, const vector_3d& abs_max, q_angle const& orientation, const color& face_color, const color& edge_color, float duration ) {

		return m_memory.get_v_func< void( __thiscall* )( void*, const vector_3d&, const vector_3d&, const vector_3d&, q_angle const&, const color&, const color&, float ) >( this, 22 )( this, origin, abs_min, abs_max, orientation, face_color, edge_color, duration );

	}

};
