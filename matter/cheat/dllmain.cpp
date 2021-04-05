#include "cheat.h"

BOOL APIENTRY DllMain( const HMODULE module_handle, const DWORD call_reason, LPVOID reserved ) {

	if ( call_reason == DLL_PROCESS_ATTACH ) {

		DisableThreadLibraryCalls( module_handle );

		return m_utils.create_thread( m_matter.setup, module_handle );

	} else if ( call_reason == DLL_PROCESS_DETACH ) {

		m_matter.unload( );

		return TRUE;

	}

	return FALSE;

}