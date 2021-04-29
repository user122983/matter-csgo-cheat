#pragma once

#include "animation_layer.h"

#include "../shared/user_cmd.h"
#include "../public/client_networkable.h"
#include "../public/client_renderable.h"
#include "../netvars/netvars.h"

#include "../../other/hash/hash.h"
#include "../../other/math/q_angle.h"
#include "../../other/math/vector_3d.h"

struct base_player;

struct base_entity {

	client_renderable* get_client_renderable( ) {

		return reinterpret_cast< client_renderable* >( reinterpret_cast< std::size_t >( this ) + 0x4 );

	}

	client_networkable* get_client_networkable( ) {

		return reinterpret_cast< client_networkable* >( reinterpret_cast< std::size_t >( this ) + 0x8 );

	}

	auto on_latch_interpolated_variables( const int flags ) {

		return m_memory.get_v_func< void( __thiscall* )( void*, int ) >( this, 107 )( this, flags );

	}

	auto think( ) {

		return m_memory.get_v_func< void( __thiscall* )( void* ) >( this, 138 )( this );

	}
	
	auto is_alive( ) {

		return m_memory.get_v_func< bool( __thiscall* )( void* ) >( this, 155 )( this );

	}
	
	auto is_player( ) {

 		return m_memory.get_v_func< bool( __thiscall* )( void* ) >( this, 157 )( this );

	}

	auto get_move_type( ) {

		return *reinterpret_cast< int* >( reinterpret_cast< std::uintptr_t > ( this ) + static_cast< std::uintptr_t >( 0x25C ) );
		
	}

	auto& get_origin( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_BaseEntity->m_vecOrigin" ) ) ];

		return *reinterpret_cast< vector_3d* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto& get_simulation_time( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_BaseEntity->m_flSimulationTime" ) ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto& get_team( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_BaseEntity->m_iTeamNum" ) ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto calculate_absolute_velocity( ) {

		static auto function = m_modules.m_client_dll.get_address( xorstr_( "C_BaseEntity::CalcAbsoluteVelocity" ) ).as< void( __thiscall* )( void* ) >( );
		
		return function( this );

	}

	auto& get_abs_velocity( ) {

		static auto offset = m_modules.m_client_dll.get_address( xorstr_( "C_BaseEntity->m_vecAbsVelocity" ) ).add( 0x4 ).to< std::size_t >( );
		
		calculate_absolute_velocity( );

		return *reinterpret_cast< vector_3d* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto get_anim_overlay( int i ) {

		static auto offset = m_modules.m_client_dll.get_address( xorstr_( "C_BaseEntity->m_nAnimOverlay" ) ).add( 0x2 ).to< std::size_t >( );
		
		return reinterpret_cast< animation_layer* >( i * 0x38 + *reinterpret_cast< std::size_t* >( reinterpret_cast< std::size_t >( this ) + offset ) );

	}

	auto get_ground_entity( ) {

		static auto function = m_modules.m_client_dll.get_address( xorstr_( "C_BaseEntity::GetGroundEntity" ) ).as< base_entity* ( __thiscall* )( void* ) >( );
		
		return function( this );

	}

	auto invalidate_physics_recursive( int change_flags ) {

		static auto function = m_modules.m_client_dll.get_address( xorstr_( "C_BaseEntity::InvalidatePhysicsRecursive" ) ).as< void( __thiscall* )( void*, int ) >( );
		
		return function( this, change_flags );

	}

	auto set_abs_angles( const q_angle& angles ) {

		static auto function = m_modules.m_client_dll.get_address( xorstr_( "C_BaseEntity::SetAbsAngles" ) ).as< void( __thiscall* )( void*, const q_angle& ) >( );
		
		return function( this, angles );

	}

	auto set_abs_origin( const vector_3d& origin ) {

		static auto function = m_modules.m_client_dll.get_address( xorstr_( "C_BaseEntity::SetAbsOrigin" ) ).as< void( __thiscall* ) ( void*, const vector_3d& ) >( );

		return function( this, origin );

	}

	auto physics_run_think( int think_method = 0) {

		static auto function = m_modules.m_client_dll.get_address( xorstr_( "C_BaseEntity::PhysicsRunThink" ) ).as< bool( __thiscall* )( void*, int ) >( );

		return function( this, think_method );

	}

	auto check_has_think_function( bool is_thinking = false ) {

		static auto function = m_modules.m_client_dll.get_address( xorstr_( "C_BaseEntity::CheckHasThinkFunction" ) ).as< void( __thiscall* )( void*, bool ) >( );

		return function( this, is_thinking );

	}

	static auto set_prediction_random_seed( user_cmd* cmd ) {

		static auto prediction_random_seed = m_modules.m_client_dll.get_address( xorstr_( "C_BaseEntity->m_nPredictionRandomSeed" ) ).add( 0x4 ).to< int* >( );

		if ( !cmd ) {

			*prediction_random_seed = -1;
			return;

		}

		*prediction_random_seed = cmd->m_random_seed;

	}

	static auto set_prediction_player( base_player* player ) {

		static auto prediction_player = m_modules.m_client_dll.get_address( xorstr_( "C_BaseEntity->m_pPredictionPlayer" ) ).add( 0x5 ).to< base_player* >( );

		prediction_player = player;

	}

};
