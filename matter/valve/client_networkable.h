#pragma once

#include "../../other/utils/utils.h"

struct client_networkable {

	auto is_dormant( ) {

		return m_utils.get_v_func< bool( __thiscall* )( void* ) >( this, 9 )( this );

	}

	auto get_index( ) {

		return m_utils.get_v_func< int( __thiscall* )( void* ) >( this, 10 )( this );

	}

};
