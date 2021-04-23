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

enum accuracy {

	accuracy_faststop

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

	void autostop( );

	void triggerbot( );
	
	void antiaim( );

	void fakelag( );
	
	void init_settings( );

	int m_fakelag_value = 0;
	
	struct {

		bool force_update;
		
		float next_update;

	} m_lby;
	
	struct {

		cs_player* pointer;

		int index;

	} m_player;

	legitbot_widgets m_settings;
	
};

inline legitbot m_legitbot;
