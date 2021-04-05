#pragma once

struct vector_2d {

	vector_2d( ) : x{ }, y{ } { }

	vector_2d( const float x, const float y ) : x{ x }, y{ y } { }

	float x, y;
	
};
