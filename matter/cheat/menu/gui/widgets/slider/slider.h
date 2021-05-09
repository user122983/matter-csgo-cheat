#pragma once

#include "../widgets.h"

struct slider : widgets {

	slider( );

	void set_range( float min, float max );
	
	void set_prefix( const std::string& prefix );

	void set_value( float value );
	
	float get_value( );

	void geometry( ) override;

	void update( ) override;

private:

	bool m_moving_slider;
	
	float m_value;
	
	float m_min;
	
	float m_max;
	
	std::string m_prefix;
	
};
