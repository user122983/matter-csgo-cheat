#include "key_binder.h"

#include "../../../menu.h"
#include "../../../../input/input.h"
#include "../../../../render/render.h"

key_binder::key_binder( ) {

	m_type = widget_type_key_binder;
	m_status = key_binder_types[ key_binder_none ];
	m_is_getting_key = false;
	m_is_getting_type = false;
	m_selected_type = key_binder_none;
	m_type_dropdown = { 51, 81 };
	
}

bool key_binder::get_state( ) {
	
	return m_is_getting_key || m_is_getting_type;
	
}

bool key_binder::get_key_state( ) {
	
	switch ( m_selected_type ) {
		
		case key_binder_none:
			return false;
		
		case key_binder_hold:
			if ( m_selected_key == 1 || m_selected_key == 2 )
				return m_input.is_mouse_down( m_selected_key );
			return m_input.is_key_down( m_selected_key );
		
		case key_binder_toggle:
			return m_input.is_key_toggled( m_selected_key );

		case key_binder_always:
			return true;
		
		default:
			return false;
		
	}
	
}

void key_binder::geometry( ) {

	std::string text = xorstr_( "[ " ) + m_status + xorstr_( " ]" );
	
	dimension text_size = m_render.get_text_size( m_render.m_fonts.smallest_pixel_7, std::wstring( text.begin( ), text.end( ) ) );
	
	m_widget_area = { get_position( ).m_x - text_size.m_width, get_position( ).m_y + 3, text_size.m_width, text_size.m_height };
	
	m_render.draw_text( m_render.m_fonts.smallest_pixel_7, m_widget_area.m_x, m_widget_area.m_y, text, m_menu.m_colors.white.at( 1 ) );
	
	if ( m_is_getting_type ) {

		area dropdown_area = { m_widget_area.m_x - 1, m_widget_area.m_y + text_size.m_height - 3, m_type_dropdown.m_width, m_type_dropdown.m_height };
		
		m_render.draw_filled_rect( dropdown_area.m_x, dropdown_area.m_y, dropdown_area.m_width, dropdown_area.m_height, m_menu.m_colors.dark.at( 2 ) );

		for ( std::size_t i = 0; i < key_binder_types.size( ); i++ ) {

			area entry_area = { dropdown_area.m_x, dropdown_area.m_y + static_cast< int >( i ) * 20, dropdown_area.m_width, 20 };

			if ( m_selected_type == i ) {

				m_render.draw_filled_rect( entry_area.m_x, entry_area.m_y, entry_area.m_width, entry_area.m_height, m_menu.m_colors.dark.at( 6 ) );
				m_render.draw_text( m_render.m_fonts.verdana, entry_area.m_x + 8, entry_area.m_y + 4, key_binder_types[ i ].data( ), m_menu.m_colors.blue.at( 0 ) );

			} else {

				m_render.draw_text( m_render.m_fonts.verdana, entry_area.m_x + 8, entry_area.m_y + 4, key_binder_types[ i ].data( ), m_menu.m_colors.white.at( 0 ) );
				
			}
			
			if ( m_input.is_key_toggled( VK_LBUTTON ) && m_input.is_mouse_in_bounds( entry_area ) && m_selected_type != i )
				m_selected_type = i;

			switch ( m_selected_type ) {

				case key_binder_none:
					m_status = key_binder_types[ key_binder_none ];
					m_selected_key = 0;
					break;

				case key_binder_toggle:
				case key_binder_hold:
					if ( !m_selected_key )
						m_status = key_binder_types[ key_binder_none ];
					break;
				
				case key_binder_always:
					m_status = key_binder_types[ key_binder_always ];
					break;
				
				default: 
					break;
				
			}
			
		}
		
		m_render.draw_outlined_rect( dropdown_area.m_x, dropdown_area.m_y, dropdown_area.m_width, dropdown_area.m_height, m_menu.m_colors.dark.at( 0 ) );

	}
	
	if ( m_is_getting_type && m_input.is_key_toggled( VK_LBUTTON ) && !m_input.is_mouse_in_bounds( { m_widget_area.m_x, m_widget_area.m_y + text_size.m_height, m_type_dropdown.m_width, m_type_dropdown.m_height } )
		and m_input.is_mouse_in_bounds( { m_parent_widget->get_position(  ).m_x, m_parent_widget->get_position( ).m_y, m_parent_widget->get_size(  ).m_width, m_parent_widget->get_size( ).m_height } ) )
		m_is_getting_type = false;
	
}

void key_binder::update( ) {
	
	if ( m_input.is_mouse_in_bounds( m_widget_area ) ) {

		if ( m_input.is_key_toggled( VK_LBUTTON ) && !m_is_getting_type ) {

			m_is_getting_key = true;

			m_input.m_listen_for_last_key = true;
			
		}

		if ( m_input.is_key_toggled( VK_RBUTTON ) && !m_is_getting_key )		
			m_is_getting_type = !m_is_getting_type;
		
	}
	
	if ( m_is_getting_key ) {

		m_status = xorstr_( "..." );

		if ( m_input.get_last_key( ) ) {
			
			m_status = m_virtual_key_codes[ m_input.get_last_key( ) ];

			m_selected_key = m_input.get_last_key( );
			
			m_is_getting_key = false;

			m_input.m_listen_for_last_key = false;

			m_input.set_last_key( 0 );

			if ( m_selected_type == key_binder_none || m_selected_type == key_binder_always )
				m_selected_type = key_binder_hold;
			
		}

	}
	
}