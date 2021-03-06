#include "module.h"

#include "../console/console.h"
#include "../xorstr/xorstr.h"

#include "../../valve/modules/modules.h"

module_info::module_info( std::size_t loaded_module ) {

	m_loaded_module = loaded_module;
	m_bitmap = reinterpret_cast< std::uint8_t* >( m_loaded_module );
	m_dos_header = reinterpret_cast< PIMAGE_DOS_HEADER >( m_loaded_module );
	m_base = m_dos_header->e_lfanew;
	m_nt_headers = reinterpret_cast< PIMAGE_NT_HEADERS >( m_loaded_module + m_base );
	m_size = m_nt_headers->OptionalHeader.SizeOfImage;

}

address pattern::find( std::string_view pattern ) {

	int* bytes = new int[ pattern.size( ) / 2 ];

	address  result = search_byte_array( bytes, build_byte_array( pattern.data( ), bytes ) );

	delete[ ] bytes;

	if ( !result )
		m_console.log( xorstr_( "failed to find pattern: %s" ), pattern.data( ) );

	return result;

}

std::size_t pattern::build_byte_array( const char* pattern, int* bytes ) {

	std::size_t count = 0;

	auto char_to_int = [ ]( char input ) -> int {

		if ( input >= '0' && input <= '9' )
			return input - '0';

		if ( input >= 'A' && input <= 'F' )
			return input - 'A' + 10;

		return input - 'a' + 10;

	};

	while ( pattern[ 0 ] && pattern[ 1 ] ) {

		if ( pattern[ 0 ] == '?' || pattern[ 1 ] == '?' ) {

			bytes[ count++ ] = -1;
			pattern += 1;

		} else if ( pattern[ 0 ] != ' ' && pattern[ 1 ] != ' ' ) {

			bytes[ count++ ] = char_to_int( pattern[ 0 ] ) * 16 + char_to_int( pattern[ 1 ] );

		}

		pattern += 1;

	}

	return count;

}

address pattern::search_byte_array( int* bytes, std::size_t size ) {

	address result;

	for ( std::size_t i = 0; i < m_size - size; i++ ) {

		bool found = true;
		for ( std::size_t j = 0; j < size; j++ ) {

			found = m_bitmap[ i + j ] == bytes[ j ] || bytes[ j ] == -1;
			if ( !found )
				break;

		}

		if ( !found )
			continue;

		result = &m_bitmap[ i ];
		break;

	}

	return result;

}

bool loaded_module::add_address( std::string_view name, std::string_view pattern, bool relative ) {

	address address = find( pattern );
	if ( !address )
		return false;

	if ( relative ) {

		address = address.relative( );
		if ( !address )
			return false;

	}

	m_functions[ m_hash.get( name ) ] = address;

	return true;

}

bool loaded_module::hook_function( std::string_view name, void* custom_function, void* hooked_function ) {

	std::size_t hash = m_hash.get( name );

	void* function;
	
	if ( !hooked_function ) {

		function = m_functions[ hash ];
		
	} else {

		function = hooked_function;
		
		m_functions[ hash ] = function;
		
	}

	if ( !function )
		return false;
	
	static auto hook = m_modules.m_gameoverlayrenderer_dll.get_address( xorstr_( "GameOverlayRenderer::HookFunc" ) ).as< bool( __cdecl* )( void*, void*, void*, int ) >( );
	if ( !hook( function, custom_function, &m_originals[ hash ], 0 ) )
		return false;

	m_console.log( xorstr_( "hooked %s -> 0x%x" ), name.data( ), function );

	return true;
}

void loaded_module::unload_functions( ) {

	static auto unhook = m_modules.m_gameoverlayrenderer_dll.get_address( xorstr_( "GameOverlayRenderer::UnhookFunc" ) ).as< void( __cdecl* )( void*, bool ) >( );
	
	for ( auto& [ k, v ] : m_functions )
		unhook( v, false );

}

bool loaded_module::valid_addresses( ) {

	for ( auto& [ k, v ] : m_functions )
		if ( !v )
			return false;

	return true;

}