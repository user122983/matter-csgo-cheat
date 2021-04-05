#pragma once

#include "base_combat_character.h"

struct user_cmd;

struct base_player : base_combat_character {

	auto& get_health( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_BasePlayer->m_iHealth" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto* get_pose_parameter( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_flPoseParameter" ) ];

		return reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	static auto util_player_by_index( const int entindex ) {

		const auto function = m_signatures.m_util_player_by_index.as< base_player* ( __thiscall* )( int ) >( );

		return function( entindex );

	}

};