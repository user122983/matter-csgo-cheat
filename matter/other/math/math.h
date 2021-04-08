#pragma once

#include "q_angle.h"
#include "vector_2d.h"
#include "vector_3d.h"

#include "../../valve/mathlib/matrix.h"

struct math {
	
	static bool world_to_screen( const vector_3d& origin, vector_2d& screen );

	static vector_3d vector_transform( const vector_3d& transform, const matrix3x4& matrix );

	float calc_fov( const q_angle& view_angle, const q_angle& aim_angle ) const;

	static q_angle calc_angle( const vector_3d& start, const vector_3d& end );

};

inline math m_math;