#pragma once

#include <algorithm>
#include <cmath>

struct q_angle {

	q_angle normalize( ) {

		this->x = std::isfinite( this->x ) ? std::remainderf( this->x, 360.f ) : 0.f;
		this->y = std::isfinite( this->y ) ? std::remainderf( this->y, 360.f ) : 0.f;
		this->z = std::clamp( this->z, -50.f, 50.f );
		
		return *this;
		
	}
	
	float x, y, z;

};
