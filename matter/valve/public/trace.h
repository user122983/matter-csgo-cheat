#pragma once

struct cplane {

	vector_3d m_normal;
	float m_dist;
	char m_type;
	char m_signbits;
	char _pad0[ 0x2 ];

};

struct base_trace {

	vector_3d m_start;	
	vector_3d m_end;		
	cplane m_plane;
	float m_fraction;		
	int	m_contents;		
	unsigned short m_disp_flags;		
	bool m_all_solid;		
	bool m_start_solid;	
	
};
