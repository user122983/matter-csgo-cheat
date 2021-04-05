#pragma once

#include "address.h"

struct stack : address {

	stack( void* address_of_return_address ) : address( m_utils.get_ebp( address_of_return_address ) ) {



	}

	stack& next( ) const {

		return *reinterpret_cast< stack* >( m_address );

	}

	template< typename t = address > t local( const std::size_t offset ) {

		return static_cast< t >( m_address - offset );

	}

	template< typename t = address > t argument( const std::size_t offset ) {

		return static_cast< t >( m_address + offset);

	}

	address return_address( ) const {

		if ( !m_address )
			return address( );

		return *reinterpret_cast< std::size_t* >( m_address + sizeof( std::size_t ) );

	}

	address address_of_return_address( ) const {

		if ( !m_address )
			return address( );

		return m_address + sizeof( std::size_t );

	}

};