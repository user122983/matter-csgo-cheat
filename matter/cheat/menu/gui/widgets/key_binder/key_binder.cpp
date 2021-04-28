#include "key_binder.h"

#include "../../definitions.h"
#include "../../../menu.h"
#include "../../../../input/input.h"
#include "../../../../render/render.h"

key_binder::key_binder( ) {

	m_type = widget_type_key_binder;
	m_status = xorstr_( "none" );
	m_type_dropdown = { 50, 42 };
	m_is_getting_key = false;
	m_is_getting_type = false;
	
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
		
		default:
			return false;
		
	}
	
}

void key_binder::geometry( ) {

	std::string text = xorstr_( "[ " ) + m_status + xorstr_( " ]" );
	dimension text_size = m_render.get_text_size( m_render.m_fonts.verdana, std::wstring( text.begin( ), text.end( ) ) );
	
	m_widget_area = { get_abs_position( ).m_x - text_size.m_width, get_abs_position( ).m_y, text_size.m_width, text_size.m_height };
	
	m_render.draw_text( m_render.m_fonts.verdana, m_widget_area.m_x, m_widget_area.m_y, text, m_menu.m_colors.white );

	int m_none_available = m_selected_key ? 0 : 1;
	m_type_dropdown.m_height = m_none_available ? 42 : 62;
	
	if ( m_is_getting_type ) {

		m_render.draw_filled_rect( m_widget_area.m_x, m_widget_area.m_y + text_size.m_height, m_type_dropdown.m_width, m_type_dropdown.m_height, m_menu.m_colors.dark3 );
		
		for ( std::size_t i = m_none_available; i < key_binder_types.size( ); i++ ) {

			area entry_area = { m_widget_area.m_x, m_widget_area.m_y + static_cast< int >( i + ( m_none_available ? 0 : 1 ) ) * 20 - 7, m_type_dropdown.m_width, 20 };

			m_render.draw_text( m_render.m_fonts.verdana, entry_area.m_x + 8, entry_area.m_y + 4, key_binder_types[ i ].data( ), m_selected_type == i ? m_menu.m_colors.blue1 : m_menu.m_colors.white );

			if ( m_input.is_key_toggled( VK_LBUTTON ) && m_input.is_mouse_in_bounds( entry_area) ) {

				m_selected_type = i;

				if ( i == 0 )
					m_is_getting_type = false;
				
			}
			
			if ( m_selected_type == 0 ) {

				m_status = xorstr_( "none" );
				m_selected_key = 0;
				m_selected_type = -1;

			}
	 
		}

	}
	
	if ( m_is_getting_type && m_input.is_key_toggled( VK_LBUTTON ) && !m_input.is_mouse_in_bounds( { m_widget_area.m_x, m_widget_area.m_y + text_size.m_height, m_type_dropdown.m_width, m_type_dropdown.m_height } )
		and m_input.is_mouse_in_bounds( { m_parent_widget->get_abs_position(  ).m_x, m_parent_widget->get_abs_position( ).m_y,  m_parent_widget->get_size(  ).m_width, m_parent_widget->get_size().m_height} ) )
		m_is_getting_type = false;
	
}

void key_binder::update( ) {
	
	if ( m_input.is_mouse_in_bounds( m_widget_area ) ) {

		if ( m_input.is_key_toggled( VK_LBUTTON ) && !m_is_getting_type )
			m_is_getting_key = m_input.m_listen_for_last_key = true;

		if ( m_input.is_key_toggled( 2 ) && !m_is_getting_key )
			m_is_getting_type = !m_is_getting_type;
		
	}
	
	if ( m_is_getting_key ) {

		m_status = xorstr_( "..." );
		
		if ( m_input.get_last_key( ) ) {

			m_status = m_virtual_key_codes[ m_input.get_last_key( ) ];
			m_is_getting_key = m_input.m_listen_for_last_key = false;
			m_selected_key = m_input.get_last_key( );
			
			if ( m_selected_type != 2 )
				m_selected_type = 1;
			
			m_input.set_last_key( 0 );

		}
		
	}
	
}