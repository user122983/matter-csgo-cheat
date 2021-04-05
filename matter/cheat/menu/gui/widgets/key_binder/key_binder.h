#pragma once

#include "../widgets.h"

#include <vector>

inline std::vector< std::string > key_binder_types {

	"None",
	"Hold",
	"Toggle"
	
};

struct key_binder final : widgets {

	key_binder( );

	bool get_state( ) const;
	
	void geometry( ) override;

	void update( ) override;

private:

	std::size_t m_selected_type = -1, m_selected_key = 0;
	std::string m_status = "none";
	bool m_is_getting_key = false, m_is_getting_type = false;
	dimension m_type_dropdown = { 50, 42 };
	
};
