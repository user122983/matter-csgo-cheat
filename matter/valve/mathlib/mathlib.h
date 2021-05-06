#pragma once

#include "mathlib_base.h"

#include <algorithm>

struct mathlib {
	
	float simple_spline( float value ) {

		float squared_value = value * value;

		return ( 3 * squared_value - 2 * squared_value * value );

	}

	float simple_spline_remap_val_clamped( float val, float a, float b, float c, float d ) {

		if ( a == b )
			return val >= b ? d : c;

		float clamped_value = ( val - a ) / ( b - a );
		clamped_value = std::clamp( clamped_value, 0.f, 1.f );
		return c + ( d - c ) * simple_spline( clamped_value );

	}

	float lerp( float percent, float a, float b ) {

		return a + ( b - a ) * percent;

	}

	vector_3d approach( vector_3d target, vector_3d value, float speed ) {

		vector_3d diff = ( target - value );

		float delta = diff.length( );
		if ( delta > speed )
			value += diff.normalized( ) * speed;
		else if ( delta < -speed )
			value -= diff.normalized( ) * speed;
		else
			value = target;

		return value;

	}

	float approach( float target, float value, float speed ) {

		float delta = target - value;

		if ( delta > speed )
			value += speed;
		else if ( delta < -speed )
			value -= speed;
		else
			value = target;

		return value;

	}

};

inline mathlib m_mathlib;