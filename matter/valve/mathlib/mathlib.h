#pragma once

#include "mathlib_base.h"

#include "../../other/math/vector_3d.h"

#include <algorithm>

struct mathlib {
	
	static float simple_spline( const float value ) {

		const auto squared_value = value * value;

		return ( 3 * squared_value - 2 * squared_value * value );

	}

	float simple_spline_remap_val_clamped( const float val, const float a, const float b, float c, float d ) const {

		if ( a == b )
			return val >= b ? d : c;

		auto clamped_value = ( val - a ) / ( b - a );
		clamped_value = std::clamp( clamped_value, 0.f, 1.f );
		return c + ( d - c ) * simple_spline( clamped_value );

	}

	static float lerp( const float percent, const float a, const float b ) {

		return a + ( b - a ) * percent;

	}

	static vector_3d approach( vector_3d target, vector_3d value, const float speed ) {

		auto diff = ( target - value );

		const auto delta = diff.length( );
		if ( delta > speed )
			value += diff.normalized( ) * speed;
		else if ( delta < -speed )
			value -= diff.normalized( ) * speed;
		else
			value = target;

		return value;

	}

	static float approach( const float target, float value, const float speed ) {

		const auto delta = target - value;

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