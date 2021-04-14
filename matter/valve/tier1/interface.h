#pragma once

using instantiate_interface_fn = void*( __cdecl* )( );

struct interface_reg {
	
	instantiate_interface_fn m_create_fn;
	const char* m_name;
	interface_reg* m_next;

};