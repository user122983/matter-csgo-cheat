#pragma once

#include "../../cheat.h"

#include <array>

enum players {

	enemy,
	team,
	local
	
};

struct visuals {

	void run( );

private:
	
	void draw_box( ) const;

	void draw_health( );

	void draw_name( ) const;

	void draw_weapon( ) const;

	void draw_ammo( ) const;

	void draw_flags( );

	void dormant_esp( );
	
	void calculate_alpha( );

	bool calculate_box( );
	
	struct {

		int left, top, right, bottom, width, height;

	} m_box = { };

	struct {

		cs_player* pointer;
		
		int index;

		bool is_dormant;

		struct {

			color white, black, blue, green, red, alpha;
			
		} m_colors = { };

	} m_player = { };

	struct {

		weapon_cs_base* pointer;

		cs_weapon_info* info;
		
	} m_weapon = { };
	
	std::array< int, 64 > m_alpha = { };

};

inline visuals m_visuals;
