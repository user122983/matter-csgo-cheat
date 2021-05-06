#include "tab_panel.h"

#include "../../../menu.h"
#include "../../../../input/input.h"
#include "../../../../render/render.h"

tab_panel::tab_panel( ) {

	m_type = widget_type_tab_panel;
	m_entry_spacing = 40;
	m_selected_entry = 1;
	
}

void tab_panel::add_tab( std::pair< std::string, std::string >& title ) {

	m_tabs.emplace_back( title );
	
}

std::size_t tab_panel::get_index( ) {

	return m_selected_entry;
	
}

void tab_panel::geometry( ) {

	for ( std::size_t i = 0; i < m_tabs.size( ); i++ ) {

		m_widget_area = { get_position( ).m_x, get_position( ).m_y + static_cast< int >( i ) * m_entry_spacing, m_size.m_width, m_size.m_height };
	
		if ( m_selected_entry == i ) {
			
			m_render.draw_text( m_render.m_fonts.matter_icons, m_widget_area.m_x + 50, m_widget_area.m_y + m_size.m_height / 2, m_tabs[ i ].first, m_menu.m_colors.white.at( 0 ), x_centre | y_centre );
			m_render.draw_text( m_render.m_fonts.verdana, m_widget_area.m_x + 80, m_widget_area.m_y + m_size.m_height / 2, m_tabs[ i ].second, m_menu.m_colors.white.at( 0 ), y_centre );
			
		} else {
			
			m_render.draw_text( m_render.m_fonts.matter_icons, m_widget_area.m_x + 50, m_widget_area.m_y + m_size.m_height / 2, m_tabs[ i ].first, m_menu.m_colors.white.at( 1 ), x_centre | y_centre );
			m_render.draw_text( m_render.m_fonts.verdana, m_widget_area.m_x + 80, m_widget_area.m_y + m_size.m_height / 2, m_tabs[ i ].second, m_menu.m_colors.white.at( 1 ), y_centre);

			if ( m_input.is_key_toggled( VK_LBUTTON ) && m_input.is_mouse_in_bounds( m_widget_area ) )
				m_selected_entry = i;
			
		}
		
	}
	
}

void tab_panel::update( ) {

	
	
}
