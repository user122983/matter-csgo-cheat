#pragma once

#include "../../other/math/vector_3d.h"

struct __declspec( align( 16 ) ) vector_aligned : vector_3d {
	
	vector_aligned( ) = default;

	vector_aligned( const vector_3d& v ) {
		
		x = v.x;
		y = v.y;
		z = v.z;
		
	}

	float w;

};
