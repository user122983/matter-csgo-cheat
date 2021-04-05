#pragma once

#include "../cheat.h"
#include "../menu/gui/definitions.h"

#include <array>

enum key_state {

	up,
	toggled,
	down

};

struct input {

	bool setup( );

	void unload( ) const;

	void think( UINT message, WPARAM w_param, LPARAM l_param );

	bool is_key_toggled( const std::size_t code ) {

		if ( m_key_states[ code ].m_state != toggled )
			return false;

		return m_key_states[ code ].m_framecount == m_interfaces.m_globals->m_framecount;

	}

	bool is_key_toggled( const std::size_t code, bool& item ) {

		if ( is_key_toggled( code ) )
			item = !item;

		return item;

	}

	bool is_key_down( const std::size_t code ) {

		return m_key_states[ code ].m_state == down;

	}

	bool is_mouse_down( const std::size_t code ) {

		return m_key_states[ code ].m_state == toggled;

	}

	bool is_mouse_in_bounds( const area area ) const {

		return m_mouse.x >= area.m_x && m_mouse.y >= area.m_y && m_mouse.x <= area.m_x + area.m_width && m_mouse.y <= area.m_y + area.m_height;

	}

	int get_last_key( ) const {
		
		return m_last_key;
		
	}
	
	void set_last_key( const int key = -1 ) {
		
		m_last_key = key;
		
	}

	int get_mouse_x( ) const {
		
		return m_mouse.x;
		
	}
	
	int get_mouse_y( ) const {
		
		return m_mouse.y;
		
	}

	bool m_listen_for_last_key;
	

private:

	static long __stdcall wnd_proc( HWND window, UINT message, WPARAM w_param, LPARAM l_param );

	WNDPROC m_original_wnd_proc = nullptr;

	int m_last_key = { };

	struct {

		int x, y;

	} m_mouse = { };

	struct key_states {

		key_state m_state;
		int m_framecount;

	};

	std::array< key_states, 256 > m_key_states = { up };

};

inline input m_input;
