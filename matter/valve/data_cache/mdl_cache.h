#pragma once

struct mdl_cache {

	auto begin_lock( ) {

		return m_memory.get_v_func< void( __thiscall* )( void* ) >( this, 33 )( this );

	}

	auto end_lock( ) {

		return m_memory.get_v_func< void( __thiscall* )( void* ) >( this, 34 )( this );

	}

};