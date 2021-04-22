#include "../hooked.h"

int __fastcall hooked::sys_engine_fn::engine_no_focus_sleep( void* ecx, void* edx ) {
	
	return 1;
	
}