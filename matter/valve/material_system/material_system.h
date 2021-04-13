#pragma once

#include "material.h"

struct material_system {

	auto find_material( char const* material_name, const char* texture_group_name, bool complain = true, const char* complain_prefix = nullptr ) {

		return m_memory.get_v_func< material* ( __thiscall* )( void*, char const*, char const*, bool, char const* ) >( this, 84 )( this, material_name, texture_group_name, complain, complain_prefix );

	}

};