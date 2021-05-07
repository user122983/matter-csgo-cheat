#pragma once

#include "../misc/definitions.h"

#include <memory>
#include <vector>

struct widgets : std::enable_shared_from_this< widgets > {

	friend struct container;
		
	void set_title( const std::string& title );
	
	void set_position( int x, int y );
	
	void set_size( int width, int height );
	
	dimension get_size( );
	
	void set_parent_widget( const std::shared_ptr< widgets >& parent );
	
	point get_position( );
	
	void set_medium( const std::shared_ptr< widgets >& medium, std::size_t page );
	
	bool is_medium_unlocked( );
	
	int get_type( );
	
	void set_lock_input( const std::shared_ptr< widgets >& widget );
	
	bool is_input_unlocked( );

protected:
	
	virtual void geometry( ) = 0;

	virtual void update( ) = 0;

	std::string m_title;
	
	point m_position;
	
	dimension m_size;
	
	area m_widget_area;
	
	std::shared_ptr< widgets > m_parent_widget;
	
	std::shared_ptr< widgets > m_medium_widget;
	
	std::vector< std::shared_ptr< widgets > > m_lock_input_widget;
	
	std::size_t m_page;
	
	std::size_t m_type;
	
};
