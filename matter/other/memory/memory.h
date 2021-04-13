#pragma once
#include "address.h"

struct memory {

	std::size_t get_ebp( void* address_of_return_address ) {

		return reinterpret_cast< std::size_t >( address_of_return_address ) - sizeof( std::size_t );

	}

	template< typename t = address > t get_v_func( address pointer, std::size_t index ) {

		return static_cast< t >( pointer.to< t* >( )[ index ] );

	}
	
};

inline memory m_memory;