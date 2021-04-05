#pragma once

#include "../../cheat/cheat.h"

enum desync_type {

	desync_none,
	desync_normal,
	desync_extended

};

enum fakelag_type {

	fakelag_none,
	fakelag_static,
	fakelag_jitter,
	fakelag_break_lag_comp

};

enum fakelag_trigger {

	trigger_on_ground,
	trigger_in_air,
	trigger_on_shot,
	trigger_on_reload

};

struct legitbot {
	
	void run( );

	bool* m_send_packet = nullptr;

	//bool m_send_packet = true;

private:

	void antiaim( ) const;

	void fakelag( ) const;
	
	struct {

		cs_player* pointer;

		csgo_player_anim_state* anim_state;

	} m_local_player = { };

	struct {

		weapon_cs_base* pointer;

		cs_weapon_info* info;

	} m_weapon = { };
	
};

inline legitbot m_legitbot;