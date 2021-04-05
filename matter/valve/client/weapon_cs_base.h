#pragma once

#include "base_entity.h"

enum weapon_type {
	
	weapon_type_knife = 0,
	weapon_type_pistol = 1,
	weapon_type_submachinegun = 2,
	weapon_type_rifle = 3,
	weapon_type_shotgun = 4,
	weapon_type_sniper = 5,
	weapon_type_machinegun = 6,
	weapon_type_c4 = 7,
	weapon_type_grenade = 9,
	
};

struct cs_weapon_info {

	char pad0[ 0x14 ];
	int m_max_clip1;
	char pad1[ 0x70 ]; 
	const char* m_hud_name; 
	char pad2[ 0x3c ];
	int m_weapon_type; 

};

struct weapon_cs_base : base_entity {

	auto& get_ammo( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( "DT_WeaponCSBase->m_iClip1" ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}
	
	auto get_max_speed( ) {

		return m_utils.get_v_func< float( __thiscall* )( void* ) >( this, 441 )( this );

	}

	auto get_cs_wpn_data( ) {

		return m_utils.get_v_func< cs_weapon_info* ( __thiscall* )( void* ) >( this, 460 )( this ); 

	}

	auto is_gun( ) {

		switch ( this->get_cs_wpn_data( )->m_weapon_type ) {

			case weapon_type_pistol:
			case weapon_type_submachinegun:
			case weapon_type_rifle:
			case weapon_type_shotgun:
			case weapon_type_sniper:
			case weapon_type_machinegun:
				return true;

		}

		return false;

	}

};