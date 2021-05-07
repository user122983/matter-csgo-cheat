#include "box.h"

#include "../../../menu.h"
#include "../../../../input/input.h"
#include "../../../../render/render.h"

box::box( ) {

	m_type = widget_type_box;
	m_size = { 178, 18 };
	m_is_open = false;
	m_selected_entry = 0;
	
}

bool box::get_state( ) {

	return m_is_open;
	
}

std::size_t box::get_index( std::size_t index ) {

	switch ( m_box_type ) {
		
		case box_type_combobox:
			return m_selected_entry;
		
		case box_type_multibox:
			return m_entries.second.at( index );
		
		default:
			return -1;
		
	}
	
}

void box::set_type( std::size_t type ) {

	m_box_type = type;
	
}

void box::add_entry( std::string_view name, unsigned int value ) {

	m_entries.first.emplace_back( name );
	m_entries.second.emplace_back( value );
	
}

void box::set_value( std::size_t index, unsigned int value ) {

	m_entries.second.at( index ) = value;
	
}

void box::geometry( ) {

	m_widget_area = { get_position( ).m_x, get_position( ).m_y, m_size.m_width, m_size.m_height };
	
	m_render.draw_gradient( m_widget_area.m_x, m_widget_area.m_y, m_widget_area.m_width, m_widget_area.m_height, m_menu.m_colors.dark.at( 1 ), m_menu.m_colors.dark.at( 2 ), false );
	m_render.draw_outlined_rect( m_widget_area.m_x, m_widget_area.m_y, m_widget_area.m_width + 1, m_widget_area.m_height + 1, m_menu.m_colors.dark.at( 0 ) );
	m_render.draw_text( m_render.m_fonts.verdana, m_widget_area.m_x + 8, m_widget_area.m_y + m_widget_area.m_height / 2 - 1, m_title, m_menu.m_colors.white.at( 0 ), y_centre );

	m_render.draw_filled_rect( ( m_widget_area.m_x + m_widget_area.m_width - 6 ) - 7, m_widget_area.m_y + ( ( m_widget_area.m_height / 2 ) - 3 ) + 2, 5, 1, m_menu.m_colors.white.at( 0 ) );
	m_render.draw_filled_rect( ( m_widget_area.m_x + m_widget_area.m_width - 6 ) - 6, m_widget_area.m_y + ( ( m_widget_area.m_height / 2 ) - 3 ) + 3, 3, 1, m_menu.m_colors.white.at( 0 ) );
	m_render.draw_filled_rect( ( m_widget_area.m_x + m_widget_area.m_width - 6 ) - 5, m_widget_area.m_y + ( ( m_widget_area.m_height / 2 ) - 3 ) + 4, 1, 1, m_menu.m_colors.white.at( 0 ) );
	
	std::string selected_text;

	for ( std::size_t i = 0; i < m_entries.first.size( ); i++ ) {

		if ( m_is_open ) {
			
			area entry_area = { m_widget_area.m_x, m_widget_area.m_y + static_cast< int >( i ) * 20 + m_widget_area.m_height, m_widget_area.m_width, 19 };
									
			if ( m_box_type == box_type_combobox && m_selected_entry == i || m_box_type == box_type_multibox && m_entries.second.at( i ) == 1 ) {

				m_render.draw_filled_rect( entry_area.m_x, entry_area.m_y, entry_area.m_width, entry_area.m_height + 1, m_menu.m_colors.dark.at( 6 ) );
				m_render.draw_text( m_render.m_fonts.verdana, entry_area.m_x + 8, entry_area.m_y + m_widget_area.m_height / 2, m_entries.first.at( i ), m_menu.m_colors.blue.at( 0 ), y_centre );

				m_render.draw_line( entry_area.m_x, entry_area.m_y - 1, entry_area.m_x, entry_area.m_y + entry_area.m_height + 1, m_menu.m_colors.dark.at( 0 ) );
				m_render.draw_line( entry_area.m_x + entry_area.m_width, entry_area.m_y + 1, entry_area.m_x + entry_area.m_width, entry_area.m_y + entry_area.m_height + 1, m_menu.m_colors.dark.at( 0 ) );

				if ( i + 1 == m_entries.first.size( ) )
					m_render.draw_line( entry_area.m_x, entry_area.m_y + entry_area.m_height + 1, entry_area.m_x + entry_area.m_width, entry_area.m_y + entry_area.m_height + 1, m_menu.m_colors.dark.at( 0 ) );
				
			} else {

				m_render.draw_filled_rect( entry_area.m_x, entry_area.m_y, entry_area.m_width, entry_area.m_height + 1, m_menu.m_colors.dark.at( 2 ) );
				m_render.draw_text( m_render.m_fonts.verdana, entry_area.m_x + 8, entry_area.m_y + m_widget_area.m_height / 2, m_entries.first.at( i ), m_menu.m_colors.white.at( 0 ), y_centre );
				
				m_render.draw_line( entry_area.m_x, entry_area.m_y - 1, entry_area.m_x, entry_area.m_y + entry_area.m_height + 1, m_menu.m_colors.dark.at( 0 ) );
				m_render.draw_line( entry_area.m_x + entry_area.m_width, entry_area.m_y + 1, entry_area.m_x + entry_area.m_width, entry_area.m_y + entry_area.m_height + 1, m_menu.m_colors.dark.at( 0 ));

				if ( i + 1 == m_entries.first.size( ) )
					m_render.draw_line( entry_area.m_x, entry_area.m_y + entry_area.m_height + 1, entry_area.m_x + entry_area.m_width, entry_area.m_y + entry_area.m_height + 1, m_menu.m_colors.dark.at( 0 ) );
				
			}
								
			if ( m_input.is_key_toggled( VK_LBUTTON ) && m_input.is_mouse_in_bounds( entry_area ) ) {

				if ( m_box_type == box_type_combobox )
					m_selected_entry = i;
				else if ( m_box_type == box_type_multibox )	
					m_entries.second[ i ] = !m_entries.second[ i ];
				 
			}

		}

		if ( m_box_type == box_type_multibox ) {
			
			bool has_reached_end = selected_text.length( ) > 12;
			bool is_first_item = selected_text.length( ) == 0;
			
			if ( m_entries.second[ i ] && !has_reached_end ) {

				if ( !is_first_item )
					selected_text.append( xorstr_( ", " ) );

				selected_text.append( m_entries.first[ i ] );

			} else if ( has_reached_end && !is_first_item ) {

				std::string three_dots = xorstr_( " ..." );
				
				if ( !( selected_text.compare( selected_text.size( ) - three_dots.size( ), three_dots.size( ), three_dots ) == 0 ) )
					selected_text.append( three_dots );
				
			}
			
		} else if ( m_box_type == box_type_combobox ) {

			if ( m_selected_entry == i )
				selected_text = m_entries.first[ i ];

		}
		
	}

	if ( selected_text.empty( ) )
		selected_text = xorstr_( "None" );
	 
	dimension text_size = m_render.get_text_size( m_render.m_fonts.verdana, std::wstring( m_title.begin( ), m_title.end( ) ) );
	m_render.draw_text( m_render.m_fonts.verdana, m_widget_area.m_x + text_size.m_width + 12, m_widget_area.m_y + m_widget_area.m_height / 2 - 1, selected_text, m_menu.m_colors.white.at( 0 ), y_centre );
	
}

void box::update( ) {

	if ( m_input.is_key_toggled( VK_LBUTTON ) ) {

		// ghetto drug dealer spotted :@!!
		
		area widget_area = { m_widget_area.m_x, m_widget_area.m_y, m_widget_area.m_width, m_widget_area.m_height - 1 };

		if ( m_input.is_mouse_in_bounds( widget_area ) )
			m_is_open = !m_is_open;

		if ( m_is_open && !m_input.is_mouse_in_bounds( widget_area )
			and m_input.is_mouse_in_bounds( { m_parent_widget->get_position( ).m_x, m_parent_widget->get_position( ).m_y, m_parent_widget->get_size( ).m_width, m_parent_widget->get_size( ).m_height } )
			and !m_input.is_mouse_in_bounds( { m_widget_area.m_x, m_widget_area.m_y + m_widget_area.m_height, m_widget_area.m_width, static_cast< int >( m_entries.first.size( ) ) * 20 } ) )

			m_is_open = false;

	}
	
}