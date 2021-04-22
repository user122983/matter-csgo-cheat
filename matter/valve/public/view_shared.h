#pragma once

struct view_setup {

	char _pad0[ 0xB0 ];
	float m_fov;
	float m_viewmodel_fov;
	vector_3d m_origin;
	char _pad1[ 0x8C ];

};
