#pragma once

#include "../mathlib/matrix.h"
#include "../mathlib/vector.h"

struct csurface {
	
	const char* m_name;
	short m_surface_props;
	unsigned short m_flags;
	
};

struct ray {

	void init( vector_3d start, vector_3d end ) {

		m_delta = end - start;
		m_is_swept = m_delta.length_sqr( ) != 0.f;
		m_extents.x = m_extents.y = m_extents.z = 0.0f;
		m_mat_world_axis_transform = nullptr;
		m_is_ray = true;
		m_start_offset.x = m_start_offset.y = m_start_offset.z = 0.0f;
		m_start = start;
		
	}
	
	vector_aligned m_start;
	vector_aligned m_delta;
	vector_aligned m_start_offset;
	vector_aligned m_extents;
	matrix3x4* m_mat_world_axis_transform;
	bool m_is_ray;
	bool m_is_swept;
	
};

