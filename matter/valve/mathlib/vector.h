#pragma once

#include "../../other/math/vector_3d.h"

struct __declspec( align( 16 ) ) vector_aligned : vector_3d {
	
	vector_aligned( ) = default;

	vector_aligned( const vector_3d& v ) {
		
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
		
	}

	float w;

};
