#pragma once

#include "../widgets.h"

#include "../../../../../other/color/color.h"

struct color_picker final : widgets {

	color_picker( );

	void geometry( ) override;

	void update( ) override;

private:

	bool m_is_open = false;
	color m_color = color( 255, 255, 255 );

};
