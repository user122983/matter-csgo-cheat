#pragma once

#include "../widgets.h"

struct slider final : widgets {

	slider( );

	void set_range( float min, float max );
	
	void set_prefix( std::string_view prefix );
	
	float get_value( ) const;
	
	void geometry( ) override;

	void update( ) override;

private:

	bool m_moving_slider = false;
	float m_value = 0.f, m_min = 0.f, m_max = 0.f;
	std::string_view m_prefix;
	
};
