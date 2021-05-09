#pragma once

#include "gui/gui.h"

#include "../../other/xorstr/xorstr.h"

enum tabs {

	tab_ragebot,
	tab_legitbot,
	tab_visuals,
	tab_world,
	tab_misc,
	tab_settings
	
};

struct legitbot_widgets {

	std::shared_ptr< checkbox > m_enabled;
	std::shared_ptr< checkbox > m_friendly_fire;
	std::shared_ptr< box > m_target;
	std::shared_ptr< checkbox > m_silent_aim;
	std::shared_ptr< slider > m_fov;
	std::shared_ptr< slider > m_smooth;
	std::shared_ptr< checkbox > m_rcs_enabled;
	std::shared_ptr< slider > m_rcs_x;
	std::shared_ptr< slider > m_rcs_y;
	std::shared_ptr< box > m_ignore;
	std::shared_ptr< box > m_accuracy;
	std::shared_ptr< slider > m_backtrack;

	std::shared_ptr< checkbox > m_triggerbot_enabled;
	std::shared_ptr< box > m_triggerbot_hitbox;
	std::shared_ptr< checkbox > m_triggerbot_friendly_fire;
	std::shared_ptr< box > m_triggerbot_ignore;
	std::shared_ptr< slider > m_triggerbot_delay;
	std::shared_ptr< slider > m_triggerbot_hitchance;

};

struct visuals_widgets {

	std::shared_ptr< checkbox > m_enabled;
	std::shared_ptr< checkbox > m_box;
	std::shared_ptr< color_picker > m_box_color;

};

struct menu {

	bool setup( );
	
	struct {
		
		std::vector< color > dark {

			color( 10, 10, 10 ),
			color( 43, 43, 43 ),
			color( 35, 35, 35 ),
			color( 22, 22, 22 ),
			color( 24, 24, 24 ),
			color( 100, 100, 100 ),
			color( 28, 28, 28 ),
			color( 70, 70, 70 ),
			color( 57, 57, 57 )
			
		};

		std::vector< color > blue {

			color( 139, 195, 235 ),
			color( 109, 165, 205 )

		};
		
		std::vector< color > white {

			color( 255, 255, 255, 200 ),
			color( 255, 255, 255, 50 )
			
		};
				 
	} m_colors;

	std::shared_ptr< container > m_menu;
	
	std::shared_ptr< tab_panel > m_tab_panel;

	std::vector< std::pair< std::string, std::string > > m_tabs {

		{ xorstr_( "1" ), xorstr_( "Ragebot" ) },
		{ xorstr_( "1" ), xorstr_( "Legitbot" ) },
		{ xorstr_( "2" ), xorstr_( "Visuals" ) },
		{ xorstr_( "3" ), xorstr_( "World" ) },
		{ xorstr_( "4" ), xorstr_( "Misc" ) },
		{ xorstr_( "5" ), xorstr_( "Settings" ) }

	};
	
	// legitbot

	legitbot_widgets m_legitbot_widgets;
	
	std::shared_ptr< container > m_legitbot_container;
	std::shared_ptr< key_binder > m_legitbot_activation;
	std::shared_ptr< box > m_legitbot_weapon;

	legitbot_widgets m_default;
	legitbot_widgets m_pistols;
	legitbot_widgets m_heavy;
	legitbot_widgets m_rifles;
	legitbot_widgets m_scout;
	legitbot_widgets m_awp;

	std::vector< legitbot_widgets > m_weapon_widgets {

		m_default,
		m_pistols,
		m_heavy,
		m_rifles,
		m_scout,
		m_awp

	};
	
	std::vector< std::string > m_weapon_names {

		xorstr_( "Default" ),
		xorstr_( "Pistols" ),
		xorstr_( "Heavy" ),
		xorstr_( "Rifles" ),
		xorstr_( "Scout" ),
		xorstr_( "Awp" )
		
	};

	std::vector< std::string > m_target_names {

		xorstr_( "Head" ),
		xorstr_( "Neck" ),
		xorstr_( "Upper chest" ),
		xorstr_( "Chest" ),
		xorstr_( "Stomach" )

	};

	std::vector< std::string > m_hitbox_names {

		xorstr_( "Head" ),
		xorstr_( "Chest" ),
		xorstr_( "Stomach" ),
		xorstr_( "Arms" ),
		xorstr_( "Legs" )

	};

	std::vector< std::string > m_ignore_names {

		xorstr_( "Flash" ),
		xorstr_( "Smoke" )

	};

	std::vector< std::string > m_accuracy_names{

		xorstr_( "Fast stop" )

	};
	
	std::shared_ptr< container > m_triggerbot_container;
	std::shared_ptr< key_binder > m_triggerbot_activation;
	
	std::shared_ptr< container > m_antiaim_container;
	std::shared_ptr< checkbox > m_antiaim_enabled;
	std::shared_ptr< box > m_antiaim_desync;
	std::shared_ptr< checkbox > m_antiaim_invert;
	std::shared_ptr< key_binder > m_antiaim_invert_activation;
	std::shared_ptr< box > m_antiaim_fakelag_type;
	std::shared_ptr< slider > m_antiaim_fakelag_value;
	std::shared_ptr< box > m_antiaim_fakelag_triggers;

	std::vector< std::string > m_desync_names {

		xorstr_( "None" ),
		xorstr_( "Normal" ),
		xorstr_( "Extended" )

	};

	std::vector< std::string > m_fakelag_names {

		xorstr_( "None" ),
		xorstr_( "Static" ),
		xorstr_( "Jitter" ),
		xorstr_( "Adaptive" )

	};

	std::vector< std::string > m_fakelag_triggers_names {

		xorstr_( "None" ),
		xorstr_( "Always" ),
		xorstr_( "On ground" ),
		xorstr_( "In air" ),
		xorstr_( "On shot" ),
		xorstr_( "On reload" )

	};
	
	// visuals
	
	std::shared_ptr< container > m_esp_container;
	std::shared_ptr< checkbox > m_esp_enabled;
	std::shared_ptr< box > m_esp_player;

	std::vector< std::string > m_player_names {

		xorstr_( "Enemy" ),
		xorstr_( "Team" ),
		xorstr_( "Local" )

	};

	visuals_widgets m_enemy;
	visuals_widgets m_team;
	visuals_widgets m_local;

	std::vector< visuals_widgets > m_esp_widgets {

		m_enemy,
		m_team,
		m_local

	};
	
	std::shared_ptr< container > m_chams_container;
	
	std::shared_ptr< container > m_hud_container;

	// misc

	std::shared_ptr< container > m_misc_container;
	std::shared_ptr< checkbox > m_server_hitboxes;
	std::shared_ptr < slider > m_fov;	
	
};

inline menu m_menu;