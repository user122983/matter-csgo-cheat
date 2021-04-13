#pragma once

struct localize {

	auto find( char const* token_name ) {

		return m_memory.get_v_func< wchar_t* ( __thiscall* )( void*, char const* ) >( this, 11 )( this, token_name );

	}

};