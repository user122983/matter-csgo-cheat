#include "../hooked.h"

bool __fastcall hooked::file_system_fn::loose_files_allowed( void* ecx, void* edx ) {
	
	return false;
	
}