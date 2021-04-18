#pragma once

#include "cmodel.h"
#include "trace.h"

struct cs_player;

struct game_trace : base_trace {

	float m_fraction_left_solid;
	csurface m_surface;
	int m_hit_group;
	short m_physics_bone;
	unsigned short m_world_surface_index;
	cs_player* m_hit_entity;
	int	m_hitbox;

};
