#include "checkbox.h"

#include "../../../menu.h"
#include "../../../../input/input.h"
#include "../../../../render/render.h"

checkbox::checkbox( ) {

	m_type = widget_type_checkbox;
	m_size = { 8, 8 };
}

bool checkbox::get_state( ) const {

	return m_is_checked;
	
}

void checkbox::geometry( ) {

	m_widget_area = { get_abs_position( ).m_x, get_abs_position( ).m_y, m_size.m_width, m_size.m_height };
	
	m_render.draw_gradient( m_widget_area.m_x, m_widget_area.m_y, m_widget_area.m_width, m_widget_area.m_height, m_is_checked ? color( 139, 195, 235 ) : color( 37, 37, 37 ), m_is_checked ? color( 129, 185, 225 ) : color( 30, 30, 30 ), false );
	m_render.draw_outlined_rect( m_widget_area.m_x, m_widget_area.m_y, m_widget_area.m_width, m_widget_area.m_height, color( 45, 45, 45 ) );
	m_render.draw_text( m_render.m_fonts.verdana, m_widget_area.m_x + m_size.m_width + 15, m_widget_area.m_y + m_size.m_height / 2 - 1, m_title, color( 255, 255, 255 ), y_centre );
	
}

void checkbox::update( ) {

	const auto text_size = m_render.get_text_size( m_render.m_fonts.verdana, std::wstring( m_title.begin( ), m_title.end( ) ) );
	const area text_area = { m_widget_area.m_x + m_size.m_width + 15, m_widget_area.m_y - text_size.m_height / 2, text_size.m_width, text_size.m_height };
	
	if ( m_input.is_key_toggled( VK_LBUTTON ) && ( m_input.is_mouse_in_bounds( m_widget_area ) || m_input.is_mouse_in_bounds( text_area ) ) )
		m_is_checked = !m_is_checked;

}