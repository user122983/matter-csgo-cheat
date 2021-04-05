#pragma once

#include "../memory/address.h"

#include <windows.h>
#include <thread>
#include <cstddef>

struct utils {
	
	static bool create_thread( DWORD WINAPI function( void* ), void* parameter );

	static void sleep( const std::size_t milliseconds ) {

		std::this_thread::sleep_for( std::chrono::milliseconds( milliseconds ) );

	}

	static std::size_t get_ebp( void* address_of_return_address ) {

		return reinterpret_cast< std::size_t >( address_of_return_address ) - sizeof( std::size_t );

	}

	template< typename t = address > static t get_v_func( address pointer, std::size_t index ) {

		return static_cast< t >( pointer.to< t* >( )[ index ] );

	}

};

inline utils m_utils;
