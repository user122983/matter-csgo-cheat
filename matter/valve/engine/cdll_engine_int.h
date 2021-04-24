#pragma once

#include "../mathlib/matrix.h"

#include "../../other/memory/memory.h"
#include "../../other/math/q_angle.h"

struct client_class;
struct bf_write;

using player_info = struct {

	char _pad0[ 0x8 ];
	int m_xuid_low;
	char _pad1[ 0x4 ];
	char m_name[ 256 ];
	char _pad2[ 0x13c ];

};

struct engine_client {

	auto get_player_info( int ent_num, player_info* info ) {

		return m_memory.get_v_func< bool( __thiscall* )( void*, int, player_info* ) >( this, 8 )( this, ent_num, info );

	}

	auto get_local_player( ) {

		return m_memory.get_v_func< int( __thiscall* )( void* ) >( this, 12 )( this );

	}

	auto is_in_game( ) {
		
		return m_memory.get_v_func< bool( __thiscall* )( void* ) >( this, 26 )( this );

	}

	auto set_view_angles( const q_angle& view_angle ) {

		m_memory.get_v_func< void( __thiscall* )( void*, const q_angle& ) >(this, 19 )( this, view_angle );

	}

	auto get_world_to_screen_matrix( ) {

		return m_memory.get_v_func< view_matrix& ( __thiscall* )( void* ) >( this, 37 )( this );

	}

};

struct base_client_dll {

	auto get_all_classes( ) {

		return m_memory.get_v_func< client_class* ( __thiscall* )( void* ) >( this, 8 )( this );

	}

	auto write_usercmd_delta_to_buffer( int slot, bf_write* buf, int from, int to, bool is_new_command ) {

		return m_memory.get_v_func< bool( __thiscall* )( void*, int, void*, int, int, bool ) >( this, 24 )( this, slot, buf, from, to, is_new_command );

	}

};