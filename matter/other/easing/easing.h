#pragma once

struct easing {

	// https://github.com/nicolausYes/easing-functions

	static double in_cubic( const double x ) {

		return x * x * x;

	}

};

inline easing m_easing;
