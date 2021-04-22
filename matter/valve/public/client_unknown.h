#pragma once

#include "../../other/memory/memory.h"

struct base_entity;

struct client_unknown {

	auto get_base_entity( ) {

		return m_memory.get_v_func< base_entity*( __thiscall* )( void* ) >(this, 4 )( this );

	}
	
};
