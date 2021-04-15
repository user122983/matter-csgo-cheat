#pragma once

#include "../public/sound_info.h"
#include "../tier1/utl_vector.h"

struct engine_sound {

	auto get_active_sounds( utl_vector< sound_info >& sound_list ) {

		m_memory.get_v_func< void( __thiscall* )( void*, utl_vector< sound_info >& ) >( this, 19 )( this, sound_list );

	}
	
};
