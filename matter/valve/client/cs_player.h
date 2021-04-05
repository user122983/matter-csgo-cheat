#pragma once

#include "base_animating.h"
#include "../mathlib/matrix.h"

enum activity {

	activity_reload,
	activity_attack,
	activity_plant,
	
};

struct csgo_player_anim_state;

struct cs_player : base_animating {

	auto& is_player_ghost( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_bIsPlayerGhost" ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto& get_third_person_recoil( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_flThirdpersonRecoil" ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto& get_duck_amount( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_flDuckAmount" ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto& get_playback_rate( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_flPlaybackRate" ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto& get_cycle( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_flCycle" ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto& get_lower_body_yaw_target( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_flLowerBodyYawTarget" ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto get_player_anim_state_csgo( ) {

		const auto offset = m_signatures.m_player_anim_state_csgo.add( 0x2 ).to< std::size_t >( );

		return *reinterpret_cast< csgo_player_anim_state** >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto get_coordinate_frame( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_BaseEntity->m_CollisionGroup" ) ] - 0x30;

		return *reinterpret_cast< matrix3x4* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto has_helmet( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_bHasHelmet" ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast<std::size_t>( this ) + offset );

	}

	auto get_armor( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_ArmorValue" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto get_money( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_iAccount" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto has_defuser( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_bHasDefuser" ) ];

		return *reinterpret_cast< bool* > ( reinterpret_cast< std::size_t > ( this ) + offset );

	}

	auto get_flash_duration( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_flFlashDuration" ) ];

		return *reinterpret_cast<float*> ( reinterpret_cast< std::size_t > ( this ) + offset );

	}

	auto is_defusing( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_bIsDefusing" ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast< std::size_t >( this ) + offset);

	}

	auto has_c4( ) {

		const auto function = m_signatures.m_has_c4.as< bool( __thiscall* )( void*)  >( );

		return function( this );

	}

	auto is_scoped( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_bIsScoped" ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto is_activity_active( int checked_activity ) {

		const auto animation_layer_weapon_action = this->get_anim_overlay( checked_activity == activity_plant ? 8 : 1 );
		if ( animation_layer_weapon_action ) {

			const auto activity = this->get_sequence_activity( animation_layer_weapon_action->m_sequence );

			switch ( checked_activity ) {
				case activity_reload:
					checked_activity = 967;
					break;
				case activity_attack:
					checked_activity = 961;
					break;
				case activity_plant:
					checked_activity = 978;
					break;
			}
			
			if ( activity == checked_activity && animation_layer_weapon_action->m_weight != 0.f )
				return true;

		}

		return false;
				
	}
	
	auto get_obb_min( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_vecMins" ) ];

		return *reinterpret_cast< vector_3d* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto get_obb_max( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_CSPlayer->m_vecMaxs" ) ];

		return *reinterpret_cast< vector_3d* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto get_spawn_time( ) {
		
		return *reinterpret_cast< float* >( reinterpret_cast< std::uintptr_t >( this ) + 0xA370 );
		
	}

	auto get_flags( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_BasePlayer->m_fFlags" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}
	
};