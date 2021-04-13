#include "cheat.h"

BOOL APIENTRY DllMain( const HMODULE module_handle, const DWORD call_reason, LPVOID reserved ) {

	if ( call_reason == DLL_PROCESS_ATTACH ) {

		DisableThreadLibraryCalls( module_handle );

		HANDLE handle = CreateThread( nullptr, 0, m_cheat.setup, module_handle, 0, nullptr );

		if ( !handle )
			return false;

		CloseHandle( handle );

		return TRUE;
		
	} else if ( call_reason == DLL_PROCESS_DETACH ) {

		m_cheat.unload( );

		return TRUE;

	}

	return FALSE;

}