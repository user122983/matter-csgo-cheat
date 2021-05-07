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
	fakelag_adaptive

};

enum fakelag_trigger {

	trigger_none,
	trigger_always,
	trigger_on_ground,
	trigger_in_air,
	trigger_on_shot,
	trigger_on_reload

};

enum accuracy {

	accuracy_faststop,

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

	void find_target( );
	
	void rcs( );

	void accuracy( );

	void triggerbot( );
	
	void antiaim( );

	void fakelag( );

	void init_settings( );

	struct {

		cs_player* pointer;

		q_angle angle;
		
		int index;
		
	} m_player;

	struct {

		q_angle angle;

		q_angle old_punch_angle;
		
	} m_rcs;
 			
};

inline legitbot m_legitbot;
