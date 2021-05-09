#pragma once

#include "../widgets.h"

#include <comcat.h>
#include <vector>

struct container : widgets {

	container( );
	
	void render( );
	
	void add_widget( std::shared_ptr< widgets >& widget );
	
	bool get_state( );

	void geometry( ) override;
	
	void update( ) override;
	
private:

	bool m_is_open;
	
	bool m_move_menu;
	
	std::vector< std::shared_ptr< widgets > > m_widgets;
	
	POINT m_cursor_delta;
	
};
