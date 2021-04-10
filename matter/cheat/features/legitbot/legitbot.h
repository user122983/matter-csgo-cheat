#pragma once

#include "../../cheat/cheat.h"
#include "../../menu/menu.h"

enum desync_type {

	desync_none,
	desync_normal,
	desync_extended

};

enum fakelag_type {

	fakelag_none,
	fakelag_static,
	fakelag_jitter,
	fakelag_adaptive

};

enum fakelag_trigger {

	trigger_on_ground,
	trigger_in_air,
	trigger_on_shot,
	trigger_on_reload

};

enum weapons {

	weapon_default,
	weapon_pistol,
	weapon_heavy,
	weapon_rifles,
	weapon_scout,
	weapon_awp

};

struct legitbot {
	
	void run( );

private:

	void aimbot( );

	void rcs( );
	
	void antiaim( );

	void fakelag( );

	int m_fakelag_value = 0;

	struct {

		float next_update;

	} m_lby = { };
	
	struct {

		cs_player* pointer;

		csgo_player_anim_state* anim_state;

	} m_local_player = { };

	struct {

		weapon_cs_base* pointer;

		cs_weapon_info* info;

		short item_definition_index;

		bool is_gun;

	} m_weapon = { };

	struct {

		cs_player* pointer;

		int index;

	} m_player = { };

	legitbot_widgets m_settings;
	
};

inline legitbot m_legitbot;
