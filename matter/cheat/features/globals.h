#pragma once

#include "../../other/math/vector_3d.h"
#include "../../valve/client/cs_player.h"

struct cs_weapon_info;
struct weapon_cs_base;

struct globals {

	struct {

		cs_player* pointer;

		user_cmd* cmd;

		vector_3d view_origin;
		
		q_angle real_angle;
		
		csgo_player_anim_state* anim_state;


	} m_local_player;

	struct {

		weapon_cs_base* pointer;

		cs_weapon_info* info;

		short item_definition_index;

		bool is_gun;

	} m_weapon;
	
	struct {

		bool cs_game_rules_captured = false;
		
	} m_game;
	
	struct {

		bool* send_packet = nullptr;
		
		float time = 0.f;
	
	} m_server;

	bool m_third_person = false;
	
};

inline globals m_globals;