#include "visuals.h"

#include "../globals.h"
#include "../../render/render.h"
#include "../../../other/math/math.h"

/* todo:
 * 
 * paddings
 * 
 */

void visuals::run( ) {
	
	std::vector< std::pair< cs_player*, float > > order;
	
	m_matter.iterate_players( [ this, &order ]( cs_player* player ) mutable -> void {

		order.emplace_back( std::make_pair( player, ( player->get_client_renderable( )->get_render_origin( ) - m_globals.m_view_origin ).length( ) ) );
				
	}, iterate_dormant );
	
	std::ranges::sort( order, [ ]( const auto& a, const auto& b ) {

		return a.second > b.second;

	} );

	for ( const auto& [ player, distance ] : order ) {

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

		dormant_esp( );

		draw_box( );

		draw_health( );

		draw_name( );

		draw_flags( );

		if ( !m_player.is_dormant ) {

			draw_ammo( );

			draw_weapon( );

		}

	}
	
}

void visuals::draw_box( ) const {

	m_render.draw_outlined_rect( m_box.left, m_box.top, m_box.width, m_box.height, m_player.m_colors.white, 0 );
	m_render.draw_outlined_rect( m_box.left - 1, m_box.top - 1, m_box.width + 2, m_box.height + 2,  m_player.m_colors.black, 0 );
	m_render.draw_outlined_rect( m_box.left + 1, m_box.top + 1, m_box.width - 2, m_box.height - 2,  m_player.m_colors.black, 0 );

}

void visuals::draw_health( ) {

	const auto health = m_player.pointer->get_health( );
	const auto scalar = static_cast< int >( 2.55 * health );

	m_render.draw_filled_rect( m_box.left - 7, m_box.top - 1, 4, m_box.height + 2, color( 0,0,0, m_alpha[ m_player.index - 1 ] ), 0 );
	
	const auto height = health * m_box.height / 100;
	m_render.draw_filled_rect( m_box.left - 6, m_box.bottom - height, 2, height, m_player.is_dormant ? m_player.m_colors.white : color( 255 - scalar, scalar, 0, m_alpha[ m_player.index - 1 ] ), 0 );
	
	if ( health == 100 )
		return;
	
	m_render.draw_text( m_render.m_fonts.smallest_pixel_7, m_box.left - 5, m_box.bottom - height - 9, m_render.format_text( "%d", health ), m_player.m_colors.white, x_centre );

}

void visuals::draw_name( ) const {

	player_info info;
	if ( !m_interfaces.m_engine->get_player_info( m_player.index, &info ) )
		return;

	m_render.draw_text( m_render.m_fonts.verdana, m_box.left + m_box.width / 2, m_box.top - 14, info.m_name, m_player.m_colors.white, x_centre );
	
}

void visuals::draw_weapon( ) const {

	auto weapon = m_interfaces.m_entity_list->get< weapon_cs_base* >( m_player.pointer->get_active_weapon( ) );
	if ( !weapon )
		return;

	const auto weapon_info = weapon->get_cs_wpn_data( );
	if ( !weapon_info )
		return;

	const std::wstring weapon_name = m_interfaces.m_localize->find( weapon_info->m_hud_name );

	m_render.draw_text( m_render.m_fonts.smallest_pixel_7, m_box.left + m_box.width / 2, m_box.bottom + 6, weapon_name, m_player.m_colors.white, x_centre );
	
}

void visuals::draw_ammo( ) const {
	
	const auto ammo = m_weapon.pointer->get_ammo( );
	const auto max_ammo = m_weapon.info->m_max_clip1;
	
	auto scalar = static_cast< float >( ammo ) / static_cast< float >( max_ammo );

	const auto animation_layer_weapon_action = m_player.pointer->get_anim_overlay( 1 );
	if ( !animation_layer_weapon_action )
		return;

	const auto activity = m_player.pointer->get_sequence_activity( animation_layer_weapon_action->m_sequence );
	if ( activity == 967 && animation_layer_weapon_action->m_weight != 0.f )
		scalar = animation_layer_weapon_action->m_cycle;

	m_render.draw_filled_rect( m_box.left - 1, m_box.bottom + 2, m_box.width + 2, 4, m_player.m_colors.black );

	m_render.draw_filled_rect( m_box.left, m_box.bottom + 3, static_cast< int> ( m_box.width * scalar ), 2, m_player.m_colors.blue );

	if ( ammo != 0 && ammo != max_ammo && activity != 967 )
		m_render.draw_text( m_render.m_fonts.smallest_pixel_7, m_box.left + ( m_box.width * scalar ), m_box.bottom - 1, std::to_string( ammo ), m_player.m_colors.white );
	
}

void visuals::draw_flags( ) {
	
	std::vector< std::pair< std::string, color > > flags;

	if ( m_player.pointer->has_helmet( ) )
		flags.emplace_back( m_player.pointer->get_armor( ) ? "hk" : "h", m_player.m_colors.white );

	if ( m_player.pointer->has_defuser( ) )
		flags.emplace_back( "kit", m_player.m_colors.white );
		
	flags.emplace_back( std::to_string( m_player.pointer->get_money( ) ) + "$", m_player.m_colors.green );

	if ( m_player.pointer->has_c4( ) )
		flags.emplace_back( "c4", m_player.m_colors.red );

	if ( m_player.pointer->is_activity_active( activity_reload ) )
		flags.emplace_back( "reload", m_player.m_colors.blue );

	if ( m_weapon.pointer->is_gun( ) && m_player.pointer->is_activity_active( activity_attack ))
		flags.emplace_back( "shot", m_player.m_colors.blue );
	
	if ( m_player.pointer->get_flash_duration( ) > 0.f )
		flags.emplace_back( "flash", m_player.m_colors.blue );

	if ( m_player.pointer->is_activity_active( activity_plant ) )
		flags.emplace_back( "plant", m_player.m_colors.blue );
	
	if ( m_player.pointer->is_defusing( ) )
		flags.emplace_back( "defuse", m_player.m_colors.red );

	if ( m_player.pointer->is_scoped( ) )
		flags.emplace_back( "scope", m_player.m_colors.blue );

	if ( m_player.is_dormant )
		flags.emplace_back( "dormant", m_player.m_colors.blue );
	
	for ( std::size_t i = 0; i < flags.size( ); ++i ) {

		const auto& [ first, second ] = flags[ i ];
		m_render.draw_text( m_render.m_fonts.smallest_pixel_7, m_box.right + 3, m_box.top - 3 + i * 9, first, second );
		
	}
		
}

void visuals::dormant_esp( ) {

	if ( m_player.is_dormant ) {

		m_player.m_colors.white = m_player.m_colors.blue = m_player.m_colors.green = m_player.m_colors.red = color( 255, 255, 255, m_alpha[ m_player.index - 1 ] );
	
	} else {

		m_player.m_colors.white = color( 255, 255, 255, m_alpha[ m_player.index - 1 ] );
		m_player.m_colors.blue = color( 0, 140, 255, m_alpha[ m_player.index - 1 ] );
		m_player.m_colors.green = color( 133, 187, 100, m_alpha[ m_player.index - 1 ] );
		m_player.m_colors.red = color( 255, 102, 128, m_alpha[ m_player.index - 1 ] );

	}

	m_player.m_colors.black = color( 0, 0, 0, m_alpha[ m_player.index - 1 ] );
	
}

void visuals::calculate_alpha( ) {

	const auto delta_time = m_interfaces.m_globals->m_curtime - m_player.pointer->get_simulation_time( );
	
	const auto opacity = delta_time > 4.f ? m_easing.in_cubic( 0.65 - std::clamp( delta_time - 4.f, 0.f, 0.65f ) ) : 0.65;

	m_alpha[ m_player.index - 1 ] = static_cast< int >( 255 * opacity );	
		
}

bool visuals::calculate_box( ) {

	const auto max = m_player.pointer->get_obb_max( );
	const auto min = m_player.pointer->get_obb_min( );
	
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

	const auto transformed = m_player.pointer->get_coordinate_frame( );

	auto left = INT_MAX, top = INT_MAX, right = INT_MIN, bottom = INT_MIN;

	std::array< vector_2d, 8 > screen;

	for ( std::size_t i = 0; i < 8; i++ ) {

		if ( !m_math.world_to_screen( m_math.vector_transform( points.at( i ), transformed ), screen.at( i ) ) )
			return false;

		const auto x = static_cast< int >( screen.at( i ).x );
		const auto y = static_cast< int >( screen.at( i ).y );

		left = min( left, x ), top = min( top, y ), right = max( right, x ), bottom = max( bottom, y );
		
	}

	m_box = {

		left, top, right, bottom, right - left, bottom - top

	};

	return true;
	
}