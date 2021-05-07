#pragma once

#include "../../cheat.h"

#include <array>

enum players {

	player_enemy,
	player_team,
	player_local
	
};

struct visuals {

	void run( );

private:
	
	void draw_box( );

	void draw_health( );

	void draw_name( );

	void draw_weapon( );

	void draw_ammo( );

	void draw_flags( );

	void dormant_esp( );

	void init_colors( );
	
	void calculate_alpha( );

	bool calculate_box( );

	struct {

		cs_player* pointer;
		
		int index;

		bool is_dormant;

	} m_player;

	struct {

		weapon_cs_base* pointer;

		cs_weapon_info* info;
		
	} m_weapon;

	struct {

		int left;
		int top;
		int right;
		int bottom;
		int width;
		int height;

	} m_box;
	
	struct {

		color white;
		color black;
		color blue;
		color green;
		color red;
		color alpha;

	} m_colors;
	
	std::array< int, 64 > m_alpha;

};

inline visuals m_visuals;
