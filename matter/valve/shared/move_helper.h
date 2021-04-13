#pragma once

#include "../../other/memory/memory.h"

struct move_helper {

	auto process_impacts( ) {

		return m_memory.get_v_func< void( __thiscall* )( void* ) >( this, 4 )( this );

	}

};
