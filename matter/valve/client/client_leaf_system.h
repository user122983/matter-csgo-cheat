#pragma once

#include <cstdint>

struct client_renderable;

struct rendable_info {

	client_renderable* m_renderable;
	char _pad0[ 0x14 ];
	std::uint16_t m_flags;
	std::uint16_t m_render_in_fast_reflection;
	char _pad1[ 0x14 ];
	
};
