#pragma once

#include "gui/widgets/container/container.h"
#include "gui/widgets/tab_panel/tab_panel.h"
#include "gui/widgets/checkbox/checkbox.h"
#include "gui/widgets/slider/slider.h"
#include "gui/widgets/key_binder/key_binder.h"
#include "gui/widgets/color_picker/color_picker.h"
#include "gui/widgets/box/box.h"

#include <memory>

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

		color white = color( 255, 255, 255 );
		color blue1 = color( 139, 195, 235 );
		color blue2 = color( 129, 185, 225 );
		

	} m_colors = { };
	
	std::shared_ptr< container > m_menu;
	
	std::shared_ptr< tab_panel > m_tab_panel;

	std::vector< std::pair< std::string, std::string > > tabs{

		{ "1", "Legitbot" }, { "2", "Visuals" }, { "3", "World" }, { "4", "Misc" }, { "5", "Settings" }

	};
	
	// legitbot

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

		"Default", "Pistols", "Heavy", "Rifles", "Scout", "Awp"
		
	};

	std::vector< std::string > m_target_names {

		"Head", "Neck", "Upper chest", "Chest", "Stomach"

	};

	std::vector< std::string > m_hitbox_names {

		"Head", "Chest", "Stomach", "Arms", "Legs"

	};

	std::vector< std::string > m_ignore_names {

		"Flash", "Smoke"

	};

	std::vector< std::string > m_accuracy_names{

		"Fast stop"

	};
	
	std::shared_ptr< container > m_triggerbot_container;
	std::shared_ptr< key_binder > m_triggerbot_activation;
	
	std::shared_ptr< container > m_antiaim_container;
	std::shared_ptr< checkbox > m_antiaim_enabled;
	std::shared_ptr< box > m_antiaim_desync;
	std::shared_ptr< box > m_antiaim_fakelag_type;
	std::shared_ptr< slider > m_antiaim_fakelag_value;
	std::shared_ptr< box > m_antiaim_fakelag_triggers;
	std::shared_ptr< slider > m_antiaim_fakelag_triggers_value;

	std::vector< std::string > m_desync_names{

		"None", "Normal", "Extended"

	};

	std::vector< std::string > m_fakelag_names {

		"None", "Static", "Jitter", "Adaptive"

	};

	std::vector< std::string > m_fakelag_triggers_names {

		"On ground", "In air", "On shot", "On reload"

	};
	
	// visuals
	
	std::shared_ptr< container > m_esp_container;
	std::shared_ptr< checkbox > m_esp_enabled;
	std::shared_ptr< box > m_esp_player;

	std::vector< std::string > m_player_names {

		"Enemy", "Team", "Local"

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