#pragma once

#include "../widgets.h"

struct checkbox : widgets {

	checkbox( );
	
	bool get_state( );

	void geometry( ) override;

	void update( ) override;

private:

	bool m_is_checked;

};
