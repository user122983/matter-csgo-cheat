#pragma once

#define fl_onground ( 1 << 0 )
#define fl_frozen ( 1 << 6 )

enum move_type {
	
	move_type_none = 0,
	move_type_noclip = 8,
	move_type_ladder = 9
	
};