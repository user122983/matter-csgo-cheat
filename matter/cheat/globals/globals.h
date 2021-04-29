#pragma once

#include "../../other/math/q_angle.h"
#include "../../other/math/vector_3d.h"

struct cs_player;
struct user_cmd;
struct cs_weapon_info;
struct weapon_cs_base;

struct globals {

	void setup( );

	void unload( );
		
	user_cmd* m_cmd;
	
	struct {

		cs_player* pointer;
				
		vector_3d view_origin;

		vector_3d eye_pos;

		bool pressed_move_key;

	} m_local_player;
	
	struct {

		weapon_cs_base* pointer;
		
		cs_weapon_info* info;

		q_angle punch_angle;
		
		bool is_gun;

		bool is_shooting;
		
	} m_weapon;
	
	struct {

		bool cs_game_rules_captured;
		
	} m_game;
	
	struct {

		bool* send_packet;
		
		float time;
	
	} m_server;

	bool m_third_person = false;
	
};

inline globals m_globals;