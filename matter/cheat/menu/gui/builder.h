#pragma once

#include "widgets/widgets.h"

struct builder {

	builder& widget( const std::shared_ptr< widgets >& widget ) {
		
		m_temp_widget = widget;

		return *this;
		
	}

	builder& position( const int x, const int y ) {
		
		m_temp_widget->set_position( x, y );

		return *this;
		
	}

	builder& size( const int width, const int height ) {
		
		m_temp_widget->set_size( width, height );

		return *this;
		
	}

	builder& spawn_in( const std::shared_ptr< container >& container ) {
		
		container->add_widget( m_temp_widget );

		return *this;
	}

	builder& medium( const std::shared_ptr< widgets >& medium, const int page = 0 ) {
		
		m_temp_widget->set_medium( medium, page );

		return *this;
		
	}

	builder& tabs( const std::vector< std::pair< std::string, std::string > >& tabs ) {
		
		for ( const auto& tab : tabs ) {
			
			std::reinterpret_pointer_cast< tab_panel >( m_temp_widget )->add_tab( tab );
			
		}
		
		return *this;
		
	}

	builder& title( const std::string_view title ) {

		m_temp_widget->set_title( title );

		return *this;

	}

	builder& entries( const std::vector< std::string >& entries ) {

		for ( const auto& entry : entries ) {

			std::reinterpret_pointer_cast< box >( m_temp_widget )->add_entry( entry );
			
		}

		return *this;

	}

	builder& type( const std::size_t type ) {

		std::reinterpret_pointer_cast< box >( m_temp_widget )->set_type( type );

		return *this;

	}

	builder& range( const float min, const float max ) {

		std::reinterpret_pointer_cast< slider >( m_temp_widget )->set_range( min, max );

		return *this;

	}

	builder& prefix( const std::string_view prefix ) {

		std::reinterpret_pointer_cast< slider >( m_temp_widget )->set_prefix( prefix );

		return *this;

	}

	builder& lock_input( const std::shared_ptr< widgets >& widget ) {

		m_temp_widget->set_lock_input( widget );

		return *this;

	}

	builder& lock_inputs ( const std::vector< std::shared_ptr< widgets > >& widgets ) {

		for ( const auto& widget : widgets ) {

			m_temp_widget->set_lock_input( widget );
			
		}

		return *this;

	}
	
private:

	std::shared_ptr< widgets > m_temp_widget = nullptr;
	
};

inline builder m_builder;