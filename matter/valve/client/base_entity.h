#pragma once

#include "animation_layer.h"

#include "../client_networkable.h"
#include "../client_renderable.h"
#include "../netvars/netvars.h"
#include "../signatures/signatures.h"

#include "../../other/hash/hash.h"
#include "../../other/math/q_angle.h"

struct base_entity {

	client_renderable* get_client_renderable( ) {

		return reinterpret_cast< client_renderable* >( reinterpret_cast< std::size_t >( this ) + 0x4 );

	}

	client_networkable* get_client_networkable( ) {

		return reinterpret_cast< client_networkable* >( reinterpret_cast< std::size_t >( this ) + 0x8 );

	}

	auto on_latch_interpolated_variables( const int flags ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, int ) >( this, 107 )( this, flags );

	}
	
	auto is_alive( ) {

		return m_utils.get_v_func< bool( __thiscall* )( void* ) >( this, 155 )( this );

	}

	auto is_player( ) {

		return m_utils.get_v_func< bool( __thiscall* )( void* ) >( this, 157 )( this );

	}

	auto& get_origin( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_BaseEntity->m_vecOrigin" ) ];

		return *reinterpret_cast< vector_3d* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto& get_simulation_time( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_BaseEntity->m_flSimulationTime" ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto& get_team( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_BaseEntity->m_iTeamNum" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto calc_absolute_velocity( ) {

		const auto function = m_signatures.m_calc_absolute_velocity.as< void( __thiscall* )( void* ) >( );

		return function( this );

	}

	auto& get_abs_velocity( ) {

		const auto offset = m_signatures.m_abs_velocity.add( 0x4 ).to< std::size_t >( );

		calc_absolute_velocity( );

		return *reinterpret_cast< vector_3d* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto get_anim_overlay( const int i ) {

		const auto offset = m_signatures.m_anim_overlay.add( 0x2 ).to< std::size_t >( );

		return reinterpret_cast< animation_layer* >( i * 0x38 + *reinterpret_cast< std::size_t* >( reinterpret_cast< std::size_t >( this ) + offset ) );

	}

	auto get_ground_entity( ) {

		const auto function = m_signatures.m_get_ground_entity.as< base_entity* ( __thiscall* )( void* ) >( );

		return function( this );

	}

	auto invalidate_physics_recursive( const int change_flags ) {

		const auto function = m_signatures.m_invalidate_physics_recursive.as< void( __thiscall* )( void*, int ) >( );

		return function( this, change_flags );

	}

	auto set_abs_angles( const q_angle& angles ) {

		const auto function = m_signatures.m_set_abs_angles.as< void( __thiscall* )( void*, const q_angle& ) >( );

		return function( this, angles );

	}

	auto set_abs_origin( const vector_3d& origin ) {

		const auto function = m_signatures.m_set_abs_origin.as< void( __thiscall* )( void*, const vector_3d& ) >( );

		return function( this, origin );

	}

};
