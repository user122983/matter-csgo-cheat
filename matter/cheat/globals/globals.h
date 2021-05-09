#pragma once

#include "../../other/math/q_angle.h"
#include "../../other/math/vector_3d.h"

struct csgo_player_anim_state;
struct cs_player;
struct user_cmd;
struct cs_weapon_info;
struct weapon_cs_base;

struct globals {

	void init( );

	// client
	
	struct {

		cs_player* pointer;

		vector_3d eye_pos;

		vector_3d view_origin;

		q_angle punch_angle;
		
	} m_local_player;

	struct {

		weapon_cs_base* pointer;

		cs_weapon_info* info;

		bool is_gun;

		bool is_shooting;
		
	} m_weapon;
	
	user_cmd* m_cmd;

	// server

	bool m_cs_game_rules_captured;
	
	bool* m_send_packet;

	float m_server_time;

	// features

	bool m_third_person;

};

inline globals m_globals;