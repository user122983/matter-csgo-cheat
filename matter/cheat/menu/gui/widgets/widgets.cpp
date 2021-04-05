#include "widgets.h"

#include "box/box.h"
#include "key_binder/key_binder.h"
#include "tab_panel/tab_panel.h"

void widgets::set_title( const std::string_view title ) {

	m_title = title.data( );
	
}

void widgets::set_position( const int x, const int y ) {

	m_position = { x, y };
	
}

void widgets::set_size( const int width, const int height ) {

	m_size = { width, height };
	
}

dimension widgets::get_size( ) const {
	
	return { m_size.m_width, m_size.m_height };
	
}

void widgets::set_parent_widget( const std::shared_ptr< widgets >& parent )  {

	m_parent_widget = parent;
	
}

point widgets::get_abs_position( ) const {

	if ( !m_parent_widget )
		return m_position;

	return { m_position.m_x + m_parent_widget->get_abs_position( ).m_x, m_position.m_y + m_parent_widget->get_abs_position( ).m_y  };
	
}

void widgets::set_medium( const std::shared_ptr< widgets >& medium, const std::size_t page ) {

	m_medium_widget = medium;
	m_page = page;
	
}

bool widgets::is_unlocked( ) const {

	if ( !m_medium_widget || m_page < 0 )
		return true;

	switch ( m_medium_widget->m_type ) {
	case widget_type_tab_panel:
		return std::reinterpret_pointer_cast< tab_panel >( m_medium_widget )->get_index( ) == m_page;
	case widget_type_box:
		return std::reinterpret_pointer_cast< box >( m_medium_widget )->get_index( ) == m_page;
	default: 
		return true;
	}

}

int widgets::get_type( ) const {
	
	return m_type;
	
}

void widgets::set_lock_input( const std::shared_ptr< widgets >& widget ) {

	m_lock_input_widget.emplace_back( widget );

}

bool widgets::is_input_unlocked( ) const {

	if ( m_lock_input_widget.empty( ) )
		return true;

	for ( const auto& widgets : m_lock_input_widget ) {
		
		switch ( widgets->m_type ) {
			case widget_type_box:
				if ( std::reinterpret_pointer_cast< box >( widgets )->get_state( ) )
					return false;
				break;
			case widget_type_key_binder:
				if ( std::reinterpret_pointer_cast< key_binder >( widgets )->get_state( ) )
					return false;
				break;
			default:
				return true;
		}
		
	}

	return true;
	
}
