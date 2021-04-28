#pragma once

#include "../../other/math/vector_3d.h"
#include "../../valve/client/cs_player.h"

struct cs_weapon_info;
struct weapon_cs_base;

struct globals {

	void setup( );

	void unload( );
		
	user_cmd* m_cmd;
	
	struct {

		cs_player* pointer;
				
		csgo_player_anim_state* anim_state;

		vector_3d view_origin;

		vector_3d eye_pos;

		q_angle aim_punch_angle;
		
		int move_type;

		int flags;

		int team;
		
		int pressed_move_key;

		bool is_alive;

		bool is_use_new_animstate;

		float spawn_time;

	} m_local_player;
	
	struct {

		weapon_cs_base* pointer;
		
		cs_weapon_info* info;

		q_angle punch_angle;
		
		short item_definition_index;

		bool is_gun;

		bool is_shooting;

		bool is_reloading;
		
	} m_weapon;
	
	struct {

		bool cs_game_rules_captured;

		bool is_freeze_period;

		bool is_valve_server;
		
	} m_game;
	
	struct {

		bool* send_packet;
		
		float time;
	
	} m_server;

	bool m_third_person = false;
	
};

inline globals m_globals;