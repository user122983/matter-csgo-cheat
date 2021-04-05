#pragma once

#include "../mathlib/matrix.h"
#include "../other/utils/utils.h"

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

	auto get_player_info( const int ent_num, player_info* info ) {

		return m_utils.get_v_func< bool( __thiscall* )( void*, int, player_info* ) >( this, 8 )( this, ent_num, info );

	}

	auto get_local_player( ) {

		return m_utils.get_v_func< int( __thiscall* )( void* ) >( this, 12 )( this );

	}

	auto is_in_game( ) {
		
		return m_utils.get_v_func< bool( __thiscall* )( void* ) >( this, 26 )( this );

	}

	auto get_world_to_screen_matrix( ) {

		return m_utils.get_v_func< view_matrix& ( __thiscall* )( void* ) >( this, 37 )( this );

	}

};

struct base_client_dll {

	auto get_all_classes( ) {

		return m_utils.get_v_func< client_class* ( __thiscall* )( void* ) >( this, 8 )( this );

	}

	auto write_usercmd_delta_to_buffer( const int slot, bf_write* buf, const int from, const int to, const bool is_new_command ) {

		return m_utils.get_v_func< bool( __thiscall* )( void*, int, void*, int, int, bool ) >( this, 24 )( this, slot, buf, from, to, is_new_command );

	}

};