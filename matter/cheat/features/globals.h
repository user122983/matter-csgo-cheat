#pragma once

#include "../../other/math/vector_3d.h"
#include "../../valve/client/cs_player.h"

struct globals {

	cs_player* m_local_player = { };

	user_cmd* m_cmd = { }; 
	
	vector_3d m_view_origin;

	bool m_third_person = false;

	bool m_cs_game_rules_captured = false;

	float m_server_time = 0.f;

	bool* m_send_packet = nullptr; 
	
};

inline globals m_globals;