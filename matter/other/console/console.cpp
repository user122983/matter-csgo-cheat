#include "console.h"

#include "../../cheat/cheat.h"

#include <iostream>

bool console::setup( const std::string_view name ) {

	if ( !m_cheat.m_debug_mode || !AllocConsole( ) )
		return false;

	freopen_s( reinterpret_cast< _iobuf** >( stdout ), "CONOUT$", "w", stdout );
	freopen_s( reinterpret_cast< _iobuf** >( stderr ), "CONOUT$", "w", stderr );

	m_handle = GetStdHandle( STD_OUTPUT_HANDLE );

	return SetConsoleTitleA( name.data( ) );

}

void console::unload( ) {

	fclose( static_cast< _iobuf* >( stdout ) );
	fclose( static_cast< _iobuf* >( stderr ) );

	FreeConsole( );

}

void console::log( std::string_view format, ... ) {

	if ( !m_cheat.m_debug_mode || std::strlen( format.data( ) ) >= sizeof( m_buffer ) )
		return;

	va_list arguments;

	va_start( arguments, format );

	std::memset( m_buffer, '\0', sizeof( m_buffer ) );
	vsprintf_s( m_buffer, format.data( ), arguments );

	SetConsoleTextAttribute( m_handle, 7 );

	std::cout << m_buffer << std::endl;

	va_end( arguments );

}