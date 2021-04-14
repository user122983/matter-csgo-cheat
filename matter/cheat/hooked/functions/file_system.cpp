#include "../hooked.h"

bool __fastcall hooked::file_system_fn::can_load_third_party_files( void* ecx, void* edx ) {
	
	return true;
	
}