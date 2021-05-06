#include "color_picker.h"

#include "../../../menu.h"
#include "../../../../input/input.h"
#include "../../../../render/render.h"

color_picker::color_picker( ) {

	m_type = widget_type_color_picker;
	m_size = { 21, 11 };
	m_is_open = false;
	m_color = m_menu.m_colors.white.at( 0 );
	
}

void color_picker::geometry( ) {

	m_widget_area = { get_position( ).m_x, get_position( ).m_y, m_size.m_width, m_size.m_height };

	m_render.draw_filled_rect( m_widget_area.m_x, m_widget_area.m_y, m_size.m_width, m_size.m_height, m_color );
	m_render.draw_outlined_rect( m_widget_area.m_x, m_widget_area.m_y, m_size.m_width, m_size.m_height, m_menu.m_colors.dark.at( 0 ) );

	if ( m_is_open ) {

		m_render.draw_filled_rect( m_widget_area.m_x, m_widget_area.m_y + m_widget_area.m_height, 120, 120, m_color );
		
	}

}

void color_picker::update( ) {

	if ( m_input.is_key_toggled( VK_LBUTTON ) && m_input.is_mouse_in_bounds( m_widget_area ) )
		m_is_open = !m_is_open;
	
}