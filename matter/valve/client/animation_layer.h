#pragma once

#include "../public/studio.h"

struct animation_layer {

	char _pad0[ 0x8 ]; 
	studio_hdr* m_dispatched_studio_hdr;
	int m_dispatched_src; 
	int m_dispatched_dst; 
	char _pad1[ 0x4 ]; 
	int m_sequence; 
	char _pad2[ 0x4 ];
	float m_weight; 
	char _pad3[ 0x4 ]; 
	float m_playback_rate; 
	float m_cycle; 

};