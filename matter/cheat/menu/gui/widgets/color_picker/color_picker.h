#pragma once

#include "../widgets.h"

#include "../../../../../other/color/color.h"

struct color_picker : widgets {

	color_picker( );

	void geometry( ) override;

	void update( ) override;

private:

	bool m_is_open;
	
	color m_color;

};
