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

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSPlayer->m_bIsPlayerGhost" ) ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto& get_third_person_recoil( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSPlayer->m_flThirdpersonRecoil" ) ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto& get_duck_amount( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSPlayer->m_flDuckAmount" ) ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto& get_playback_rate( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSPlayer->m_flPlaybackRate" ) ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto& get_cycle( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSPlayer->m_flCycle" ) ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto& get_lower_body_yaw_target( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSPlayer->m_flLowerBodyYawTarget" ) ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto& get_eye_angles( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSPlayer->m_angEyeAngles" ) ) ];

		return *reinterpret_cast< q_angle* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto& get_killed_by_taser( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSPlayer->m_bKilledByTaser" ) ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto get_player_anim_state_csgo( ) {

		static auto offset = m_modules.m_client_dll.get_address( xorstr_( "C_CSPlayer->m_PlayerAnimStateCSGO" ) ).add( 0x2 ).to< std::size_t >( );
		
		return *reinterpret_cast< csgo_player_anim_state** >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto get_coordinate_frame( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_BaseEntity->m_CollisionGroup" ) ) ] - 0x30;

		return *reinterpret_cast< matrix3x4* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto has_helmet( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSPlayer->m_bHasHelmet" ) ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast<std::size_t>( this ) + offset );

	}

	auto get_armor( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSPlayer->m_ArmorValue" ) ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto get_money( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSPlayer->m_iAccount" ) ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto has_defuser( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSPlayer->m_bHasDefuser" ) ) ];

		return *reinterpret_cast< bool* > ( reinterpret_cast< std::size_t > ( this ) + offset );

	}

	auto get_flash_duration( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSPlayer->m_flFlashDuration" ) ) ];

		return *reinterpret_cast<float*> ( reinterpret_cast< std::size_t > ( this ) + offset );

	}

	auto is_defusing( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSPlayer->m_bIsDefusing" ) ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast< std::size_t >( this ) + offset);

	}

	auto has_c4( ) {

		static auto function = m_modules.m_client_dll.get_address(xorstr_( "C_CSPlayer::HasC4" ) ).as< bool( __thiscall* )( void* ) >( );

		return function( this );

	}

	auto is_scoped( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSPlayer->m_bIsScoped" ) ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto is_activity_active( int checked_activity ) {

		animation_layer* animation_layer_weapon_action = get_anim_overlay( checked_activity == activity_plant ? 8 : 1 );
		if ( animation_layer_weapon_action ) {

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
				
				default: 
					break;
				
			}
			
			if ( get_sequence_activity( animation_layer_weapon_action->m_sequence ) == checked_activity && animation_layer_weapon_action->m_weight != 0.f )
				return true;

		}

		return false;
				
	}
	
	auto get_obb_min( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSPlayer->m_vecMins" ) ) ];

		return *reinterpret_cast< vector_3d* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto get_obb_max( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSPlayer->m_vecMaxs" ) ) ];

		return *reinterpret_cast< vector_3d* >( reinterpret_cast< std::size_t >( this ) + offset );

	}
	
	auto get_flags( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_BasePlayer->m_fFlags" ) ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto get_shots_fired( ) {
		 
		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSPlayer->m_iShotsFired" ) ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto get_aim_punch_angle( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSPlayer->m_aimPunchAngle" ) ) ];

		return *reinterpret_cast< q_angle* >( reinterpret_cast< std::size_t >( this ) + offset);

	}

	auto& get_velocity( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSPlayer->m_vecVelocity[0]" ) ) ];

		return *reinterpret_cast< vector_3d* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto& get_use_new_animstate( ) {

		static auto offset = m_modules.m_client_dll.get_address( xorstr_( "C_CSPlayer->m_bUseNewAnimstate" ) ).add( 0x2 ).to< std::size_t >( );
		
		return *reinterpret_cast< bool* >( reinterpret_cast< std::size_t >( this ) + offset );

	}
	 
	auto& get_spawn_time( ) {

		static auto offset = m_modules.m_client_dll.get_address( xorstr_( "C_CSPlayer->m_flSpawnTime" ) ).add( 0x2 ).to< std::size_t >( );

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );
		
	}

	auto get_eye_pos( ) {

		vector_3d eye_pos;
		
		m_memory.get_v_func< void ( __thiscall* )( void*, vector_3d& ) >( this, 168 )( this, eye_pos );
		
		return eye_pos;

	}
	
	auto eye_angles( ) {

		return m_memory.get_v_func< q_angle& ( __thiscall* )( void* ) >( this, 169 )( this );

	}
	
	auto handle_taser_animation( ) {
		 
		static auto function = m_modules.m_client_dll.get_address( xorstr_( "C_CSPlayer::HandleTaserAnimation" ) ).as< void( __thiscall* )( void* ) >( );
		
		return function( this );

	}

};