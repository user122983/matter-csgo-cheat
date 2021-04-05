#pragma once

#include "../memory/address.h"

#include <windows.h>
#include <cstddef>
#include <cstdint>
#include <string>

struct module_info {

	module_info( ) = default;

	module_info( std::size_t the_module );

	address find_pattern( std::string_view pattern ) const;

	std::size_t get_module( ) const {
		
		return m_module;
		
	}

private:

	static std::size_t build_byte_array( const char* pattern, int* bytes );
	
	address search_byte_array( int* bytes, std::size_t size ) const;

	std::size_t m_module;
	std::uint8_t* m_bitmap;
	PIMAGE_DOS_HEADER m_dos_header;
	long m_base;
	PIMAGE_NT_HEADERS m_nt_headers;
	unsigned long m_size;
	
};