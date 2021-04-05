#include "utils.h"

bool utils::create_thread( DWORD WINAPI function( void* ), void* parameter ) {

	const auto handle = CreateThread( nullptr, 0, function, parameter, 0, nullptr );

	if ( !handle )
		return false;

	CloseHandle( handle );

	return true;

}