#include "slider.h"

#include "../../../menu.h"
#include "../../../../input/input.h"
#include "../../../../render/render.h"

#include <algorithm>

slider::slider( ) {
	 
	m_type = widget_type_slider;
	m_size = { 178, 7 };
	m_moving_slider = false;
	m_min = 0.f;
	m_max = 0.f;
	m_value = 0.f;
	
}

void slider::set_range( float min, float max ) {

	m_min = min;
	m_max = max;
	
}

void slider::set_prefix( const std::string& prefix ) {

	m_prefix = prefix;
	
}

void slider::set_value( float value ) {

	m_value = value;
	
}

float slider::get_value( ) {
	
	return m_value;
	
}

void slider::geometry( ) {

	m_widget_area = { get_abs_position( ).m_x, get_abs_position( ).m_y, m_size.m_width, m_size.m_height };

	dimension text_size = m_render.get_text_size( m_render.m_fonts.verdana, std::wstring( m_title.begin( ), m_title.end( ) ) );
	m_render.draw_text( m_render.m_fonts.verdana, m_widget_area.m_x, m_widget_area.m_y - text_size.m_height - 2, m_title, m_menu.m_colors.white1 );

	std::string value_text = std::to_string( static_cast< int >( m_value ) );
	if ( !m_prefix.empty( ) )
		value_text = value_text + xorstr_( " " ) + m_prefix;
	
	m_render.draw_text( m_render.m_fonts.verdana, m_widget_area.m_x + m_widget_area.m_width - m_render.get_text_size( m_render.m_fonts.verdana, std::wstring( value_text.begin( ), value_text.end( ) ) ).m_width, m_widget_area.m_y - text_size.m_height - 2, value_text, m_menu.m_colors.white1 );

	m_render.draw_gradient( m_widget_area.m_x, m_widget_area.m_y, m_widget_area.m_width, m_widget_area.m_height, m_menu.m_colors.dark1, m_menu.m_colors.dark2, false );
	m_render.draw_gradient( m_widget_area.m_x + 1, m_widget_area.m_y + 1, m_value / m_max * ( m_size.m_width - 2 ), 5, m_menu.m_colors.blue1, m_menu.m_colors.blue3, false );

}

void slider::update( ) {

	if ( m_input.is_key_toggled( VK_LBUTTON ) && m_input.is_mouse_in_bounds( m_widget_area ) )
		m_moving_slider = true;

	if ( m_moving_slider )
		m_value = std::clamp( static_cast< float >( m_input.get_mouse_x( ) - m_widget_area.m_x ) / m_widget_area.m_width * m_max, m_min, m_max );
	
	if ( !m_input.is_mouse_down( VK_LBUTTON ) )
		m_moving_slider = false;
	
}