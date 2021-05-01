#pragma once

#include "q_angle.h"
#include "vector_2d.h"
#include "vector_3d.h"

#include "../../valve/mathlib/matrix.h"

struct math {
	
	bool world_to_screen( const vector_3d& origin, vector_2d& screen );

	vector_3d vector_transform( vector_3d& transform, matrix3x4& matrix );

	float calculate_fov( q_angle& view_angle, const q_angle& aim_angle );

	q_angle calculate_angle( const vector_3d& start, const vector_3d& end );

};

inline math m_math;