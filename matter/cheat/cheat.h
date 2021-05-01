#pragma once

#include "../other/other.h"
#include "../valve/valve.h"

#include <functional>

enum iterate_player_flags {

	iterate_dead = 1,
	iterate_dormant = 1 << 1,
	iterate_teammates = 1 << 2,

};

struct cheat {

	static DWORD WINAPI setup( void* parameter );

	void unload( );

	void iterate_players( const std::function< void( cs_player* ) >& function, int flags = { } );
	
	HWND m_window;

	bool m_debug_mode;

};

inline cheat m_cheat;
