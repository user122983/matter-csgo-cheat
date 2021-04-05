#pragma once

#include "vector_2d.h"
#include "vector_3d.h"

#include "../../valve/mathlib/matrix.h"

struct math {
	
	static bool world_to_screen( const vector_3d& origin, vector_2d& screen );

	static vector_3d vector_transform( const vector_3d& transform, const matrix3x4& matrix );

};

inline math m_math;