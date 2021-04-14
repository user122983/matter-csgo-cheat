#pragma once

struct sound_info {

	int m_guid;
	void* m_file_name;
	int	m_sound_source;
	int	m_channel;
	int	m_speaker_entity;
	float m_volume;
	float m_last_spatialized_volume;
	float m_radius;
	int	m_pitch;
	vector_3d* m_origin;
	vector_3d* m_direction;
	
};