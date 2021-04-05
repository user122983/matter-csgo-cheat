#pragma once

struct client_renderable {

	auto& get_render_origin( ) {

		return m_utils.get_v_func< vector_3d& ( __thiscall* )( void* ) >( this, 1 )( this );

	}

	auto get_render_bounds( vector_3d& mins, vector_3d& maxs ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, vector_3d&, vector_3d& ) >( this, 17 )( this, mins, maxs );

	}

};
