#pragma once

using change_callback = void(  __cdecl* )( void*, const char*, float );

struct convar {

	auto find_var( const char* variable_name ) {

		return m_memory.get_v_func< convar*( __thiscall* )( void*, const char* ) >( this, 15 )( this, variable_name );

	}

	auto get_float( )  {
		
		std::uint32_t xored = *reinterpret_cast< std::uint32_t* >( &m_parent->m_float_value ) ^ reinterpret_cast< std::uint32_t >( this );
		return *reinterpret_cast< float* >( &xored );
		
	}

	char _pad0[ 0x4 ];
	convar* m_next;				
	bool m_registered;		
	const char* m_name;				
	const char* m_help_string;		
	int	m_flags;				
	char _pad1[ 0x4 ];			
	convar* m_parent;			
	const char* m_default_value;		
	char* m_string;			
	int m_string_length;		
	float m_float_value;			
	int	m_int_value;				
	bool m_has_min;			
	float m_min_value;			
	bool m_has_max;			
	float m_max_value;			
	utl_vector< change_callback > m_change_callbacks;
	
};