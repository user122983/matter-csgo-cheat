#include "visuals.h"

#include "../../menu/menu.h"
#include "../../render/render.h"

void visuals::run( ) {

	if ( !m_globals.m_local_player.pointer )
		return;

	dormant_esp( );
	
	std::vector< std::pair< cs_player*, float > > order;
	
	m_cheat.iterate_players( [ this, &order ]( cs_player* player ) {

		order.emplace_back( std::make_pair( player, ( player->get_client_renderable( )->get_render_origin( ) - m_globals.m_local_player.view_origin ).length( ) ) );
				
	}, iterate_dormant );
	
	std::ranges::sort( order, [ ]( auto& a, auto& b ) {

		return a.second > b.second;

	} );

	for ( auto& [ player, distance ] : order ) {

		m_player = {

			player,
			player->get_client_networkable( )->get_index( ),
			player->get_client_networkable( )->is_dormant( ),

		};
		
		m_weapon.pointer = m_interfaces.m_entity_list->get< weapon_cs_base* >( m_player.pointer->get_active_weapon( ) );
		if ( !m_weapon.pointer )
			continue;

		m_weapon.info = m_weapon.pointer->get_cs_wpn_data( );
		if ( !m_weapon.info )
			continue;
		
		if ( !calculate_box( ) )
			continue;

		calculate_alpha( );

		init_colors( );

		draw_box( );

		draw_health( );

		draw_name( );

		draw_ammo( );

		draw_weapon( );

		draw_flags( );

	}
	
}

void visuals::draw_box( ) {

	if ( !m_menu.m_esp_widgets[ player_enemy ].m_box->get_state( ) )
		return;
	
	m_render.draw_outlined_rect( m_box.left, m_box.top, m_box.width, m_box.height, m_colors.white, 0 );
	m_render.draw_outlined_rect( m_box.left - 1, m_box.top - 1, m_box.width + 2, m_box.height + 2,  m_colors.black, 0 );
	m_render.draw_outlined_rect( m_box.left + 1, m_box.top + 1, m_box.width - 2, m_box.height - 2,  m_colors.black, 0 );

}

void visuals::draw_health( ) {

	int health = m_player.pointer->get_health( );
	int scalar = static_cast< int >( 2.55 * health );

	m_render.draw_filled_rect( m_box.left - 7, m_box.top - 1, 4, m_box.height + 2, color( 0,0,0, m_alpha[ m_player.index - 1 ] ), 0 );
	
	int height = health * m_box.height / 100;
	m_render.draw_filled_rect( m_box.left - 6, m_box.bottom - height, 2, height, m_player.is_dormant ? m_colors.white : color( 255 - scalar, scalar, 0, m_alpha[ m_player.index - 1 ] ), 0 );
	
	if ( health == 100 )
		return;
	
	m_render.draw_text( m_render.m_fonts.smallest_pixel_7, m_box.left - 5, m_box.bottom - height - 9, m_render.format_text( "%d", health ), m_colors.white, x_centre );

}

void visuals::draw_name( ) {

	player_info info;
	if ( !m_interfaces.m_engine->get_player_info( m_player.index, &info ) )
		return;

	m_render.draw_text( m_render.m_fonts.verdana, m_box.left + m_box.width / 2, m_box.top - 14, info.m_name, m_colors.white, x_centre );
	
}

void visuals::draw_weapon( ) {

	weapon_cs_base* weapon = m_interfaces.m_entity_list->get< weapon_cs_base* >( m_player.pointer->get_active_weapon( ) );
	if ( !weapon )
		return;

	cs_weapon_info* weapon_info = weapon->get_cs_wpn_data( );
	if ( !weapon_info )
		return;

	std::wstring weapon_name = m_interfaces.m_localize->find( weapon_info->m_hud_name );

	m_render.draw_text( m_render.m_fonts.smallest_pixel_7, m_box.left + m_box.width / 2, m_box.bottom + 6, weapon_name, m_colors.white, x_centre );
	
}

void visuals::draw_ammo( ) {
	
	int ammo = m_weapon.pointer->get_ammo( );
	int max_ammo = m_weapon.info->m_max_clip1;
	
	float scalar = static_cast< float >( ammo ) / static_cast< float >( max_ammo );

	animation_layer* animation_layer_weapon_action = m_player.pointer->get_anim_overlay( 1 );
	if ( !animation_layer_weapon_action )
		return;

	int activity = m_player.pointer->get_sequence_activity( animation_layer_weapon_action->m_sequence );
	if ( activity == 967 && animation_layer_weapon_action->m_weight != 0.f )
		scalar = animation_layer_weapon_action->m_cycle;

	m_render.draw_filled_rect( m_box.left - 1, m_box.bottom + 2, m_box.width + 2, 4, m_colors.black );

	m_render.draw_filled_rect( m_box.left, m_box.bottom + 3, static_cast< int> ( m_box.width * scalar ), 2, m_colors.blue );

	if ( ammo != 0 && ammo != max_ammo && activity != 967 )
		m_render.draw_text( m_render.m_fonts.smallest_pixel_7, m_box.left + ( m_box.width * scalar ), m_box.bottom - 1, std::to_string( ammo ), m_colors.white );
	
}

void visuals::draw_flags( ) {
	
	std::vector< std::pair< std::string, color > > flags;

	if ( m_player.pointer->has_helmet( ) )
		flags.emplace_back( m_player.pointer->get_armor( ) ? xorstr_( "hk" ) : xorstr_( "h" ), m_colors.white );

	if ( m_player.pointer->has_defuser( ) )
		flags.emplace_back( xorstr_( "kit" ), m_colors.white );

	std::string last_place_name = std::string( m_player.pointer->get_last_place_name( ) );
	 
	if ( !last_place_name.empty( ) )  {

		std::wstring last_place_name_wstring = std::wstring( m_interfaces.m_localize->find( last_place_name.data( ) ) );		
		flags.emplace_back( std::string( last_place_name_wstring.begin( ), last_place_name_wstring.end( ) ), m_colors.white );
		
	}	
	
	flags.emplace_back( std::to_string( m_player.pointer->get_money( ) ) + xorstr_( "$" ), m_colors.green );

	if ( m_player.pointer->has_c4( ) )
		flags.emplace_back( xorstr_( "c4" ), m_colors.red );

	if ( m_player.pointer->is_activity_active( activity_reload ) )
		flags.emplace_back( xorstr_( "reload" ), m_colors.blue );

	if ( m_weapon.pointer->is_gun( ) && m_player.pointer->is_activity_active( activity_attack ))
		flags.emplace_back( xorstr_( "shot" ), m_colors.blue );
	
	if ( m_player.pointer->get_flash_duration( ) > 0.f )
		flags.emplace_back( xorstr_( "flash" ), m_colors.blue );

	if ( m_player.pointer->is_activity_active( activity_plant ) )
		flags.emplace_back( xorstr_( "plant" ), m_colors.blue );
	
	if ( m_player.pointer->is_defusing( ) )
		flags.emplace_back( xorstr_( "defuse" ), m_colors.red );

	if ( m_player.pointer->is_scoped( ) )
		flags.emplace_back( xorstr_( "scope" ), m_colors.blue );

	if ( m_player.is_dormant )
		flags.emplace_back( xorstr_( "dormant" ), m_colors.blue );
	
	for ( std::size_t i = 0; i < flags.size( ); ++i ) {

		auto& [ first, second ] = flags[ i ];
		m_render.draw_text( m_render.m_fonts.smallest_pixel_7, m_box.right + 3, m_box.top - 3 + i * 9, first, second );
		
	}
		
}

void visuals::dormant_esp( ) {

	// todo: reset on round_start
	
	static utl_vector< sound_info > sound_list;

	sound_list.remove_all( );
	m_interfaces.m_engine_sound->get_active_sounds( sound_list );

	static int sound_guid[ 64 ];
	for ( int i = 0; i < sound_list.count( ); i++ ) {

		sound_info& sound_element = sound_list.element( i );

		if ( sound_element.m_sound_source < 1 || sound_element.m_sound_source > 64 || sound_element.m_channel != 4 )
			continue;

		cs_player* player = m_interfaces.m_entity_list->get< cs_player* >( sound_list.element( i ).m_sound_source );

		if ( !player || !player->get_client_networkable( )->is_dormant( ) )
			continue;

		if ( sound_guid[ sound_element.m_sound_source ] < sound_element.m_guid && sound_element.m_origin && !sound_element.m_origin->is_zero( ) ) {

			sound_guid[ sound_element.m_sound_source ] = sound_element.m_guid;

			player->set_abs_origin( *sound_element.m_origin );

		}

	}
	
}

void visuals::init_colors( ) {

	if ( m_player.is_dormant ) {
		
		m_colors.white = m_colors.blue = m_colors.green = m_colors.red = color( 255, 255, 255, m_alpha[ m_player.index - 1 ] );
		
	} else {

		m_colors.white = color( 255, 255, 255, m_alpha[ m_player.index - 1 ] );
		m_colors.blue = color( 0, 140, 255, m_alpha[ m_player.index - 1 ] );
		m_colors.green = color( 133, 187, 100, m_alpha[ m_player.index - 1 ] );
		m_colors.red = color( 255, 102, 128, m_alpha[ m_player.index - 1 ] );

	}

	m_colors.black = color( 0, 0, 0, m_alpha[ m_player.index - 1 ] );
	
}

void visuals::calculate_alpha( ) {

	float delta_time = m_interfaces.m_globals->m_curtime - m_player.pointer->get_simulation_time( );
	
	float opacity = delta_time > 4.f ? m_easing.in_cubic( 0.65 - std::clamp( delta_time - 4.f, 0.f, 0.65f ) ) : 0.7f;

	m_alpha[ m_player.index - 1 ] = static_cast< int >( 255 * opacity );	
		
}

bool visuals::calculate_box( ) {

	vector_3d max = m_player.pointer->get_obb_max( );
	vector_3d min = m_player.pointer->get_obb_min( );
	
	std::array< vector_3d, 8 > points = {
		
		vector_3d( min.x, min.y, min.z ),
		vector_3d( min.x, max.y, min.z ),
		vector_3d( max.x, max.y, min.z ),
		vector_3d( max.x, min.y, min.z ),
		vector_3d( max.x, max.y, max.z ),
		vector_3d( min.x, max.y, max.z ),
		vector_3d( min.x, min.y, max.z ),
		vector_3d( max.x, min.y, max.z )
		
	};

	matrix3x4 transformed = m_player.pointer->get_coordinate_frame( );

	int left = INT_MAX, top = INT_MAX, right = INT_MIN, bottom = INT_MIN;

	std::array< vector_2d, 8 > screen;

	for ( std::size_t i = 0; i < 8; i++ ) {

		if ( !m_math.world_to_screen( m_math.vector_transform( points.at( i ), transformed ), screen.at( i ) ) )
			return false;

		int x = static_cast< int >( screen.at( i ).x );
		int y = static_cast< int >( screen.at( i ).y );

		left = min( left, x ), top = min( top, y ), right = max( right, x ), bottom = max( bottom, y );
		
	}

	m_box = {

		left, top, right, bottom, right - left, bottom - top

	};

	return true;
	
}