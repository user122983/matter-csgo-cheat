#pragma once

#include "../widgets/widgets.h"
#include "../widgets/box/box.h"
#include "../widgets/slider/slider.h"
#include "../widgets/tab_panel/tab_panel.h"
#include "../widgets/container/container.h"

struct builder {

	builder& widget( const std::shared_ptr< widgets >& widget ) {
		
		m_widget = widget;

		return *this;
		
	}

	builder& position( int x, int y ) {
		
		m_widget->set_position( x, y );

		return *this;
		
	}

	builder& size( int width, int height ) {
		
		m_widget->set_size( width, height );

		return *this;
		
	}

	builder& spawn_in( const std::shared_ptr< container >& container ) {
		
		container->add_widget( m_widget );
		
		return *this;
	}

	builder& medium( const std::shared_ptr< widgets >& medium, int page = 0 ) {
		
		m_widget->set_medium( medium, page );

		return *this;
		
	}

	builder& tabs( std::vector< std::pair< std::string, std::string > >& tabs ) {
		
		for ( auto& tab : tabs ) {
			
			std::reinterpret_pointer_cast< tab_panel >( m_widget )->add_tab( tab );
			
		}
		
		return *this;
		
	}

	builder& title( const std::string& title ) {

		m_widget->set_title( title );

		return *this;

	}

	builder& entries( std::vector< std::string >& entries ) {

		for ( auto& entry : entries ) {

			std::reinterpret_pointer_cast< box >( m_widget )->add_entry( entry );
			
		}

		return *this;

	}

	builder& type( std::size_t type ) {

		std::reinterpret_pointer_cast< box >( m_widget )->set_type( type );

		return *this;

	}

	builder& range( float min, float max ) {

		std::reinterpret_pointer_cast< slider >( m_widget )->set_range( min, max );

		return *this;

	}

	builder& prefix( const std::string& prefix ) {

		std::reinterpret_pointer_cast< slider >( m_widget )->set_prefix( prefix );

		return *this;

	}

	builder& value( float value ) {

		std::reinterpret_pointer_cast< slider >( m_widget )->set_value( value );

		return *this;

	}

	builder& lock_input( const std::shared_ptr< widgets >& widget ) {

		m_widget->set_lock_input( widget );

		return *this;

	}

	builder& lock_inputs( const std::vector< std::shared_ptr< widgets > >& widgets ) {

		for ( auto& widget : widgets ) {

			m_widget->set_lock_input(widget);

		}

		return *this;

	}

private:

	std::shared_ptr< widgets > m_widget;
	
};

inline builder m_builder;