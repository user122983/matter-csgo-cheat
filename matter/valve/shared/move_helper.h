#pragma once

#include "../../other/utils/utils.h"

struct move_helper {

	auto process_impacts( ) {

		return m_utils.get_v_func< void( __thiscall* )( void* ) >( this, 4 )( this );

	}

};
