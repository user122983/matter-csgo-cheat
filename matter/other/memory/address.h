#pragma once

#include <cstddef>
#include <cstdint>

struct address {

	address( ) : m_address{ } {



	}

	address( const std::size_t address) : m_address{ address } {



	}

	address( void* address ) : m_address{ reinterpret_cast< std::size_t >( address ) } {



	}

	operator std::size_t( ) const {

		return m_address;

	}

	operator void* () const {

		return reinterpret_cast< void* >( m_address );

	}


	bool operator==( address address ) {

		return as< std::size_t >( ) == address.as< std::size_t >( );

	}

	bool operator!=( address address ) {

		return as< std::size_t >( ) != address.as< std::size_t >( );

	}

	template< typename t = address > t to( ) {

		return *( t* )m_address;

	}

	template< typename t = address > t as( ) {

		return m_address ? ( t )m_address : t( );

	}

	template< typename t = address > t at( const std::size_t offset ) {

		return m_address ? *( t* )( m_address + offset ) : t( );

	}

	template< typename t = address > t add( const std::size_t offset ) {

		return m_address ? ( t )( m_address + offset ) : t( );

	}

	template< typename t = address > t sub( const std::size_t offset ) {

		return m_address ? ( t )( m_address - offset ) : t( );

	}

	template< typename t = address > t get( std::size_t dereferences = 1 ) {

		if ( !m_address )
			return t( );

		auto object = m_address;

		while (dereferences--)
			if (object)
				object = *reinterpret_cast<std::size_t*>(object);

		return ( t )object;

	}

	template< typename t = std::size_t > void set( const t& value ) {

		if ( !m_address )
			return;

		*( t* )m_address = value;

	}

	template< typename t = address > t relative( const std::size_t offset = 0x1 ) {

		if ( !m_address )
			return t( );

		const auto new_address = m_address + offset;

		const auto relative_offset = *reinterpret_cast< std::int32_t* >( new_address );

		if ( !relative_offset )
			return t( );

		return ( t )( new_address + sizeof( std::size_t ) + relative_offset );

	}

protected:

	std::size_t m_address;

};