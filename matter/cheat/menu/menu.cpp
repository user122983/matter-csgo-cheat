#include "menu.h"

bool menu::setup( ) {

	m_menu = std::make_shared< container >( );
	m_builder.widget( m_menu ).size( 860, 540 ).position( 400, 400 );

	m_tab_panel = std::make_shared< tab_panel >( );
	m_builder.widget( m_tab_panel ).size( 200, 40 ).position( 0, 150 ).tabs( m_tabs ).spawn_in( m_menu );

	// legitbot
	
	m_legitbot_container = std::make_shared< container >( );
	m_builder.widget( m_legitbot_container ).size( 285, 480 ).position( 230, 30 ).title( xorstr_( "Legitbot" ) ).spawn_in( m_menu ).medium( m_tab_panel, tab_legitbot );
	
	m_legitbot_activation = std::make_shared< key_binder >( );
	m_builder.widget( m_legitbot_activation ).position( 233, 25 ).spawn_in( m_legitbot_container );

	m_legitbot_weapon = std::make_shared< box >( );
	m_builder.widget( m_legitbot_weapon ).position( 54, 54 ).title( xorstr_( "Weapon:" ) ).entries( m_weapon_names ).spawn_in( m_legitbot_container ).type( box_type_combobox ).lock_input( m_legitbot_activation );

	// triggerbot

	m_triggerbot_container = std::make_shared< container >( );
	m_builder.widget( m_triggerbot_container ).size( 285, 225 ).position( 545, 30 ).title( xorstr_( "Triggerbot" ) ).spawn_in( m_menu ).medium( m_tab_panel, tab_legitbot );

	m_triggerbot_activation = std::make_shared< key_binder >( );
	m_builder.widget( m_triggerbot_activation ).position( 233, 25 ).spawn_in( m_triggerbot_container );
	
	for ( std::size_t i = 0; i < m_weapon_widgets.size( ); i++ ) {

		m_weapon_widgets[ i ].m_enabled = std::make_shared< checkbox >( );
		m_builder.widget( m_weapon_widgets[ i ].m_enabled ).position( 30, 30 ).title( i == 0 ? xorstr_( "Enabled" ) : xorstr_( "Override" ) ).spawn_in( m_legitbot_container ).medium( m_legitbot_weapon, i );
		
		m_weapon_widgets[ i ].m_friendly_fire = std::make_shared< checkbox >( );
		m_builder.widget( m_weapon_widgets[ i ].m_friendly_fire ).position( 30, 87 ).title( xorstr_( "Friendly fire" ) ).spawn_in( m_legitbot_container ).medium( m_legitbot_weapon, i );

		m_weapon_widgets[ i ].m_target = std::make_shared< box >( );
		m_builder.widget( m_weapon_widgets[ i ].m_target ).position( 54, 111 ).title( xorstr_( "Target:" ) ).entries( m_target_names ).spawn_in( m_legitbot_container ).medium( m_legitbot_weapon, i ).type( box_type_combobox );
		
		m_weapon_widgets[ i ].m_silent_aim = std::make_shared< checkbox >( );
		m_builder.widget( m_weapon_widgets[ i ].m_silent_aim ).position( 30, 144 ).title( xorstr_( "Silent aim" ) ).spawn_in( m_legitbot_container ).medium( m_legitbot_weapon, i ).lock_input( m_weapon_widgets[ i ].m_target );

		m_weapon_widgets[ i ].m_fov = std::make_shared< slider >( );
		m_builder.widget( m_weapon_widgets[ i ].m_fov ).position( 54, 179 ).title( xorstr_( "Fov" ) ).spawn_in( m_legitbot_container ).medium( m_legitbot_weapon, i ).range( 0.f, 180.f ).lock_input( m_legitbot_weapon ).lock_input( m_weapon_widgets[ i ].m_target );

		m_weapon_widgets[ i ].m_smooth = std::make_shared< slider >( );
		m_builder.widget( m_weapon_widgets[ i ].m_smooth ).position( 54, 212 ).title( xorstr_( "Smooth" ) ).spawn_in( m_legitbot_container ).medium( m_legitbot_weapon, i ).range( 0.f, 100.f ).prefix( xorstr_( "%" ) ).lock_input( m_weapon_widgets[ i ].m_target );

		m_weapon_widgets[ i ].m_rcs_enabled = std::make_shared< checkbox >( );
		m_builder.widget( m_weapon_widgets[ i ].m_rcs_enabled ).position( 30, 234 ).title( xorstr_( "Recoil control" ) ).spawn_in( m_legitbot_container ).medium( m_legitbot_weapon, i );

		m_weapon_widgets[ i ].m_rcs_x = std::make_shared< slider >( );
		m_builder.widget( m_weapon_widgets[ i ].m_rcs_x ).position( 54, 267 ).title( xorstr_( "X" ) ).spawn_in( m_legitbot_container ).medium( m_legitbot_weapon, i ).range( 0.f, 100.f ).prefix( xorstr_( "%" ) );

		m_weapon_widgets[ i ].m_rcs_y = std::make_shared< slider >( );
		m_builder.widget( m_weapon_widgets[ i ].m_rcs_y ).position( 54, 300 ).title( xorstr_( "Y" ) ).spawn_in( m_legitbot_container ).medium( m_legitbot_weapon, i ).range(0.f, 100.f ).prefix( xorstr_( "%" ) );

		m_weapon_widgets[ i ].m_ignore = std::make_shared< box >( );
		m_builder.widget( m_weapon_widgets[ i ].m_ignore ).position( 54, 325 ).title( xorstr_( "Ignore:" ) ).entries( m_ignore_names ).spawn_in( m_legitbot_container ).medium( m_legitbot_weapon, i ).type( box_type_multibox );

		m_weapon_widgets[ i ].m_accuracy = std::make_shared< box >( );
		m_builder.widget( m_weapon_widgets[ i ].m_accuracy ).position( 54, 358 ).title( xorstr_( "Accuracy:" ) ).entries( m_accuracy_names ).spawn_in( m_legitbot_container ).medium( m_legitbot_weapon, i ).type( box_type_multibox ).lock_input( m_weapon_widgets[ i ].m_ignore );
		 
		m_weapon_widgets[ i ].m_backtrack = std::make_shared< slider >( ); 
		m_builder.widget( m_weapon_widgets[ i ].m_backtrack ).position( 54, 402 ).title( xorstr_( "Backtrack" ) ).spawn_in( m_legitbot_container ).medium( m_legitbot_weapon, i ).range( 0.f, 400.f ).prefix( xorstr_( "ms" ) );

		m_weapon_widgets[ i ].m_triggerbot_enabled = std::make_shared< checkbox >( );
		m_builder.widget( m_weapon_widgets[ i ].m_triggerbot_enabled ).position( 30, 30 ).title( i == 0 ? xorstr_( "Enabled" ) : xorstr_( "Override" ) ).spawn_in( m_triggerbot_container ).medium( m_legitbot_weapon, i );

		m_weapon_widgets[ i ].m_triggerbot_hitbox = std::make_shared< box >( );
		m_builder.widget( m_weapon_widgets[ i ].m_triggerbot_hitbox ).position( 54, 54 ).title( xorstr_( "Hitbox:" ) ).entries( m_hitbox_names ).spawn_in( m_triggerbot_container ).type( box_type_multibox ).lock_input( m_triggerbot_activation );

		m_weapon_widgets[ i ].m_triggerbot_friendly_fire = std::make_shared< checkbox >( );
		m_builder.widget( m_weapon_widgets[ i ].m_triggerbot_friendly_fire ).position( 30, 87 ).title( xorstr_( "Friendly fire" ) ).spawn_in( m_triggerbot_container ).medium( m_legitbot_weapon, i ).lock_input( m_weapon_widgets[ i ].m_triggerbot_hitbox );

		m_weapon_widgets[ i ].m_triggerbot_ignore = std::make_shared< box >( );
		m_builder.widget( m_weapon_widgets[ i ].m_triggerbot_ignore ).position( 54, 111 ).title( xorstr_( "Ignore:" ) ).entries( m_ignore_names ).spawn_in( m_triggerbot_container ).medium( m_legitbot_weapon, i ).type( box_type_multibox ).lock_input( m_weapon_widgets[ i ].m_triggerbot_hitbox );

		m_weapon_widgets[ i ].m_triggerbot_delay = std::make_shared< slider >( );
		m_builder.widget( m_weapon_widgets[ i ].m_triggerbot_delay ).position( 54, 155 ).title( xorstr_( "Delay" ) ).spawn_in( m_triggerbot_container ).medium( m_legitbot_weapon, i ).range( 0.f, 100.f ).prefix( xorstr_( "ms" ) ).lock_input( m_weapon_widgets[ i ].m_triggerbot_hitbox ).lock_input( m_weapon_widgets[ i ].m_triggerbot_ignore );

		m_weapon_widgets[ i ].m_triggerbot_hitchance = std::make_shared< slider >( );
		m_builder.widget( m_weapon_widgets[ i ].m_triggerbot_hitchance ).position( 54, 185 ).title( xorstr_( "Hitchance" ) ).spawn_in( m_triggerbot_container ).medium( m_legitbot_weapon, i ).range(0.f, 100.f ).prefix( xorstr_( "%" ) );
		
	}
	
	// antiaim
	
	m_antiaim_container = std::make_shared< container >( );
	m_builder.widget( m_antiaim_container ).size( 285, 225 ).position( 545, 285 ).title( xorstr_( "Antiaim" ) ).spawn_in( m_menu ).medium( m_tab_panel, tab_legitbot );

	m_antiaim_enabled = std::make_shared< checkbox >( );
	m_builder.widget( m_antiaim_enabled ).position( 30, 30 ).title( xorstr_( "Enabled" ) ).spawn_in( m_antiaim_container );

	m_antiaim_desync = std::make_shared< box >( );
	m_builder.widget( m_antiaim_desync ).position( 54, 54 ).title( xorstr_( "Desync:" ) ).entries( m_desync_names ).spawn_in( m_antiaim_container ).type( box_type_combobox );

	m_antiaim_invert = std::make_shared< checkbox >( );
	m_builder.widget( m_antiaim_invert ).position( 30, 87 ).title( xorstr_( "Invert" ) ).spawn_in( m_antiaim_container );

	m_antiaim_invert_activation = std::make_shared< key_binder >( );
	m_builder.widget( m_antiaim_invert_activation ).position( 233, 84 ).spawn_in( m_antiaim_container );
	 
	m_antiaim_fakelag_type = std::make_shared< box >( );
	m_builder.widget( m_antiaim_fakelag_type ).position( 54, 110 ).title( xorstr_( "Fakelag:" ) ).entries( m_fakelag_names ).spawn_in( m_antiaim_container ).type( box_type_combobox ).lock_input( m_antiaim_desync );
	
	m_antiaim_fakelag_value = std::make_shared< slider >( );
	m_builder.widget( m_antiaim_fakelag_value ).position( 54, 154 ).title( xorstr_( "Choke:" ) ).spawn_in( m_antiaim_container ).range( 0.f, 15.f ).prefix( xorstr_( "ticks" ) ).lock_input( m_antiaim_fakelag_type );
	
	m_antiaim_fakelag_triggers = std::make_shared< box >( );
	m_builder.widget( m_antiaim_fakelag_triggers ).position( 54, 176 ).title( xorstr_( "Trigger:" ) ).entries( m_fakelag_triggers_names ).spawn_in( m_antiaim_container ).type( box_type_combobox ).lock_input( m_antiaim_fakelag_type );

	// esp
	
	m_esp_container = std::make_shared< container >( );
	m_builder.widget( m_esp_container ).size( 285, 480 ).position( 230, 30 ).title( xorstr_( "Esp" ) ).spawn_in( m_menu ).medium( m_tab_panel, tab_visuals );

	m_esp_player = std::make_shared< box >( );
	m_builder.widget( m_esp_player ).position( 54, 54 ).title( xorstr_( "Player:" ) ).entries( m_player_names ).spawn_in( m_esp_container ).type( box_type_combobox );

	for ( std::size_t i = 0; i < m_esp_widgets.size( ); i++ ) {

		m_esp_widgets[ i ].m_enabled = std::make_shared< checkbox >( );
		m_builder.widget( m_esp_widgets[ i ].m_enabled ).position( 30, 30 ).title( xorstr_( "Enabled" ) ).spawn_in( m_esp_container ).medium( m_esp_player, i );

		m_esp_widgets[ i ].m_box = std::make_shared< checkbox >( );
		m_builder.widget( m_esp_widgets[ i ].m_box ).position( 30, 87 ).title( xorstr_( "Box" ) ).spawn_in( m_esp_container ).medium( m_esp_player, i ).lock_input( m_esp_player );

		m_esp_widgets[ i ].m_box_color = std::make_shared< color_picker >( );
		m_builder.widget( m_esp_widgets[ i ].m_box_color ).position( 211, 87 ).spawn_in( m_esp_container ).medium( m_esp_player, i ).lock_input( m_esp_player );
		
	}
		
	// chams
	
	m_chams_container = std::make_shared< container >( );
	m_builder.widget( m_chams_container ).size( 285, 225 ).position( 545, 30 ).title( xorstr_( "Chams" ) ).spawn_in( m_menu ).medium( m_tab_panel, tab_visuals );

	// hud
	
	m_hud_container = std::make_shared< container >( );
	m_builder.widget( m_hud_container ).size( 285, 225 ).position( 545, 285 ).title( xorstr_( "Hud" ) ).spawn_in( m_menu ).medium( m_tab_panel, tab_visuals );

	// misc

	m_misc_container = std::make_shared< container >( );
	m_builder.widget( m_misc_container ).size( 285, 480 ).position( 230, 30 ).title( xorstr_( "Misc" ) ).spawn_in( m_menu ).medium( m_tab_panel, tab_misc );

	m_server_hitboxes = std::make_shared< checkbox >( );
	m_builder.widget( m_server_hitboxes ).position( 30, 30 ).title( xorstr_( "Server hitboxes" ) ).spawn_in( m_misc_container );

	m_fov = std::make_shared< slider >( );
	m_builder.widget( m_fov ).position( 54, 62 ).title( xorstr_( "Fov" ) ).spawn_in( m_misc_container ).range( 0.f, 200.f ).value( 100.f );
	
	return true;
	
}
