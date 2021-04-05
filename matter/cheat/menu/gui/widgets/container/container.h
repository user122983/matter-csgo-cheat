#pragma once

#include "../widgets.h"

#include <comcat.h>
#include <vector>

struct container final : widgets {

	container( );
	
	void render( );
	
	void add_widget( const std::shared_ptr< widgets >& widget );
	
	bool get_state( ) const;
	
	void geometry( ) override;
	
	void update( ) override;
	
private:

	bool m_is_open = true, m_move_menu = false;
	std::vector< std::shared_ptr< widgets > > m_widgets;
	POINT m_cursor_delta = { };
	
};
