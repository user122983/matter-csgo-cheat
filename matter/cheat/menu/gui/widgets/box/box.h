#pragma once

#include "../widgets.h"

enum box_type {

	box_type_combobox,
	box_type_multibox
	
};

struct box : widgets {

	box( );
	
	bool get_state( );
	
	std::size_t get_index( std::size_t index = 0 );
	
	void set_type( std::size_t type );
	
	void add_entry( std::string_view name, unsigned int value = 0 );
	
	void set_value( std::size_t index, unsigned int value );

	void geometry( ) override;

	void update( ) override;
	 
private:

	bool m_is_open;
	
	std::size_t m_box_type;

	std::size_t m_selected_entry;
	
	std::pair< std::vector< std::string >, std::vector< std::size_t > > m_entries;
	
};
