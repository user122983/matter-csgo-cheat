#pragma once

struct easing {

	// https://github.com/nicolausYes/easing-functions

	double in_cubic( double x ) {

		return x * x * x;

	}

};

inline easing m_easing;
