#pragma once

#include "../../../other/math/q_angle.h"

struct misc {

	void run( );

	void bunnyhop( );

	void autostrafe( );
	
	void movement_fix( q_angle& angle );

};

inline misc m_misc;