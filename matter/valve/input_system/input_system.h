#pragma once

struct input_system {

	auto enable_input( bool enable ) {

		return m_memory.get_v_func< void* ( __thiscall*)( void*, bool ) >( this, 11 )( this, enable );

	}

	auto reset_input_state( ) {

		return m_memory.get_v_func< void* ( __thiscall* )( void* ) >( this, 39 )( this );

	}

};
