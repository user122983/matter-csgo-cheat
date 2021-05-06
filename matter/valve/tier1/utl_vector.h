#pragma once

#include "utl_memory.h"

template < class t > void destruct( t* memory ) {
	
	memory->~t( );
	
}

template< class t, class a = utl_memory< t > > struct utl_vector {
	
	t& element( int i ) {
		
		return m_memory[ i ];
		
	}
	
	int count( ) {

		return m_size;
		
	}

	void remove_all( ) {

		for ( int i = m_size; --i >= 0; )
			destruct( &element( i ) );

		m_size = 0;
		
	}

protected:

	a m_memory;
	int m_size;
	t* m_elements;
	
};