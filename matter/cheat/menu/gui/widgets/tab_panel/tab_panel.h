#pragma once

#include "../widgets.h"

#include <vector>

struct tab_panel : widgets {

	tab_panel( );
	
	void add_tab( std::pair< std::string, std::string >& title );
	
	std::size_t get_index( );
	
	void geometry( ) override;

	void update( ) override;

private:

	int m_entry_spacing;

	std::size_t m_selected_entry;
	
	std::vector< std::pair< std::string, std::string > > m_tabs;

};
