#include "container.h"

#include "../../../menu.h"
#include "../../../../input/input.h"
#include "../../../../render/render.h"

container::container( ) {

	m_type = widget_type_container;
	m_is_open = true;
	m_move_menu = false;
	
}

void container::render() {
	
	if ( !m_input.is_key_toggled( VK_PRIOR, m_is_open ) )		
		return;

	update( );
	geometry( );
	
}

void container::add_widget( std::shared_ptr< widgets >& widget ) {

	widget->set_parent_widget( shared_from_this( ) );
	
	m_widgets.emplace( m_widgets.begin( ), widget );
	
}

bool container::get_state( ) {
	
	return m_is_open;
	
}

void container::geometry( ) {

	m_widget_area = { get_position( ).m_x, get_position( ).m_y, m_size.m_width, m_size.m_height };

	if ( !m_parent_widget ) {
		
		m_render.draw_filled_rect( m_widget_area.m_x, m_widget_area.m_y, m_widget_area.m_width, m_widget_area.m_height, m_menu.m_colors.dark.at(4 ) );
		m_render.draw_filled_rect( m_widget_area.m_x, m_widget_area.m_y, 200, m_widget_area.m_height, m_menu.m_colors.dark.at( 3 ) );
		
		m_render.draw_line( m_widget_area.m_x + 200, m_widget_area.m_y, m_widget_area.m_x + 200, m_widget_area.m_y + m_widget_area.m_height - 1, m_menu.m_colors.dark.at( 1 ) );
		m_render.draw_line( m_widget_area.m_x + 201, m_widget_area.m_y, m_widget_area.m_x + 201, m_widget_area.m_y + m_widget_area.m_height - 1, m_menu.m_colors.dark.at( 0 ) );

		m_render.draw_outlined_rect( m_widget_area.m_x, m_widget_area.m_y, m_widget_area.m_width, m_widget_area.m_height, m_menu.m_colors.dark.at( 1 ) );
		m_render.draw_outlined_rect( m_widget_area.m_x - 1, m_widget_area.m_y - 1, m_widget_area.m_width + 2, m_widget_area.m_height + 2, m_menu.m_colors.dark.at( 5 ) );
		m_render.draw_outlined_rect( m_widget_area.m_x - 2, m_widget_area.m_y - 2, m_widget_area.m_width + 4, m_widget_area.m_height + 4, m_menu.m_colors.dark.at( 5 ) );
		m_render.draw_outlined_rect( m_widget_area.m_x - 3, m_widget_area.m_y - 3, m_widget_area.m_width + 6, m_widget_area.m_height + 6, m_menu.m_colors.dark.at( 5 ) );
		m_render.draw_outlined_rect( m_widget_area.m_x - 4, m_widget_area.m_y - 4, m_widget_area.m_width + 8, m_widget_area.m_height + 8, m_menu.m_colors.dark.at( 5 ) );
		m_render.draw_outlined_rect( m_widget_area.m_x - 5, m_widget_area.m_y - 5, m_widget_area.m_width + 10, m_widget_area.m_height + 10, m_menu.m_colors.dark.at( 1 ) );

	} else {

		m_render.draw_filled_rect( m_widget_area.m_x, m_widget_area.m_y, m_widget_area.m_width, m_widget_area.m_height, m_menu.m_colors.dark.at( 3 ) );
		m_render.draw_text( m_render.m_fonts.verdana, m_widget_area.m_x + 30, m_widget_area.m_y, m_title, m_menu.m_colors.white.at( 0 ), y_centre );

		m_render.draw_line( m_widget_area.m_x, m_widget_area.m_y, m_widget_area.m_x + 28, m_widget_area.m_y, m_menu.m_colors.dark.at( 1 ) );
		m_render.draw_line( m_widget_area.m_x, m_widget_area.m_y, m_widget_area.m_x, m_widget_area.m_y + m_widget_area.m_height, m_menu.m_colors.dark.at( 1 ) );
		m_render.draw_line( m_widget_area.m_x, m_widget_area.m_y + m_widget_area.m_height, m_widget_area.m_x + m_widget_area.m_width, m_widget_area.m_y + m_widget_area.m_height, m_menu.m_colors.dark.at( 1 ) );
		m_render.draw_line( m_widget_area.m_x + m_widget_area.m_width, m_widget_area.m_y + m_widget_area.m_height, m_widget_area.m_x + m_widget_area.m_width, m_widget_area.m_y, m_menu.m_colors.dark.at( 1 ) );

		m_render.draw_line( m_widget_area.m_x - 1, m_widget_area.m_y - 1, m_widget_area.m_x + 28, m_widget_area.m_y - 1, m_menu.m_colors.dark.at( 0 ) );
		m_render.draw_line( m_widget_area.m_x - 1, m_widget_area.m_y - 1, m_widget_area.m_x - 1, m_widget_area.m_y + m_widget_area.m_height + 1, m_menu.m_colors.dark.at( 0 ) );
		m_render.draw_line( m_widget_area.m_x - 1, m_widget_area.m_y + 1 + m_widget_area.m_height, m_widget_area.m_x + m_widget_area.m_width + 1, m_widget_area.m_y + m_widget_area.m_height + 1, m_menu.m_colors.dark.at( 0 ) );
		m_render.draw_line( m_widget_area.m_x + m_widget_area.m_width + 1, m_widget_area.m_y + m_widget_area.m_height + 1, m_widget_area.m_x + m_widget_area.m_width + 1, m_widget_area.m_y - 1, m_menu.m_colors.dark.at( 0 ) );
		
		dimension text_size = m_render.get_text_size( m_render.m_fonts.verdana, std::wstring( m_title.begin( ), m_title.end( ) ) );
		m_render.draw_line( m_widget_area.m_x + 32 + text_size.m_width, m_widget_area.m_y, m_widget_area.m_x + m_widget_area.m_width, m_widget_area.m_y, m_menu.m_colors.dark.at( 1 ) );
		m_render.draw_line( m_widget_area.m_x + 31 + text_size.m_width, m_widget_area.m_y - 1, m_widget_area.m_x + m_widget_area.m_width - 1, m_widget_area.m_y - 1, m_menu.m_colors.dark.at( 0 ) );

	}
	
	for ( auto& widgets : m_widgets ) {

		if ( widgets->is_medium_unlocked( ) ) {

			if ( widgets->is_input_unlocked( ) )
				widgets->update( );
			
			widgets->geometry( );
			
		}
		
	}

}

void container::update( ) {

	if ( m_parent_widget )
		return;
	
	area movable_area = { m_position.m_x, m_position.m_y, 200, m_size.m_height };
	
	if ( m_input.is_key_toggled( VK_LBUTTON ) && m_input.is_mouse_in_bounds( movable_area ) ) {

		m_move_menu = true;

		m_cursor_delta = { m_input.get_mouse_x( ) - m_position.m_x, m_input.get_mouse_y( ) - m_position.m_y };

	}

	if ( m_move_menu )
		m_position = { m_input.get_mouse_x( ) - m_cursor_delta.x, m_input.get_mouse_y( ) - m_cursor_delta.y };
	
	if ( !m_input.is_mouse_down( 1 ) )
        m_move_menu = false;
	
}
