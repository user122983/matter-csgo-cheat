#pragma once

#include "../widgets.h"

struct checkbox final : widgets {

	checkbox( );
	
	bool get_state( ) const;
	
	void geometry( ) override;

	void update( ) override;

private:

	bool m_is_checked = false;

};
