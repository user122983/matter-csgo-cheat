#pragma once

#include "../../other/math/vector_3d.h"
#include "../../valve/client/cs_player.h"

struct globals {

	cs_player* m_local_player = { };

	user_cmd* m_cmd = { }; 
	
	vector_3d m_view_origin;

	bool m_third_person = false;
	
};

inline globals m_globals;