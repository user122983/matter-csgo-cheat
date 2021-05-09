#pragma once

#include "../widgets.h"

#include "../../../../../other/xorstr/xorstr.h"

inline std::vector< std::string > key_binder_types {

	xorstr_( "None" ),
	xorstr_( "Hold" ),
	xorstr_( "Toggle" ),
	xorstr_( "Always" )

};

enum key_binder_type {

	key_binder_none,
	key_binder_hold,
	key_binder_toggle,
	key_binder_always
	
};

struct key_binder : widgets {

	key_binder( );

	bool get_state( );

	bool get_key_state( );

	void geometry( ) override;

	void update( ) override;

private:

	std::size_t m_selected_type;
	
	std::size_t m_selected_key;
	
	std::string m_status;
	
	bool m_is_getting_key;
	
	bool m_is_getting_type;
	
	dimension m_type_dropdown;
	
};
