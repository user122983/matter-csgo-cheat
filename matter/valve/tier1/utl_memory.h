#pragma once

template< class t, class i = int > struct utl_memory {

	t& operator[ ]( i i ) {
		
		return m_memory[ i ];
		
	}

protected:

	t* m_memory;
	int m_allocation_count;
	int m_grow_size;
	
};