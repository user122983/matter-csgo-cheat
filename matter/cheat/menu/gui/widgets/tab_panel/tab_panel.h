#pragma once

#include "../widgets.h"

#include <vector>

struct tab_panel final : widgets {

	tab_panel( );
	
	void add_tab( std::pair< std::string, std::string >& title );
	
	std::size_t get_index( );
	
	void geometry( ) override;

	void update( ) override;

private:

	std::uint16_t m_entry_spacing = 40;
	std::size_t m_selected_entry = 0;
	std::vector< std::pair< std::string, std::string > > m_tabs;

};
