#pragma once

struct input_system {

	auto enable_input(const bool enable) {

		return m_utils.get_v_func< void* ( __thiscall*)( void*, bool ) >( this, 11 )( this, enable );

	}

	auto reset_input_state( ) {

		return m_utils.get_v_func< void* ( __thiscall* )( void* ) >( this, 39 )( this );

	}

};
