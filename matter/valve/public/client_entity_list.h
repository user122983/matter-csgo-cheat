#pragma once

struct client_entity_list {

	auto get_client_entity( int entity_number ) {

		return m_memory.get_v_func< void* ( __thiscall* )( void*, int ) >( this, 3 )( this, entity_number );

	}

	auto get_client_entity_from_handle( std::size_t entity ) {

		return m_memory.get_v_func< void* ( __thiscall* )( void*, std::size_t ) >( this, 4 )( this, entity );

	}

	template< class t > t get( int entity_number ) {

		return static_cast< t >( get_client_entity( entity_number ) );

	}

	template< class t > t get( std::size_t entity ) {

		return static_cast< t >( get_client_entity_from_handle( entity ) );

	}

};
