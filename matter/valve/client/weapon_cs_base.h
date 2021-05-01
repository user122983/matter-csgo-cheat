#pragma once

#include "base_entity.h"
#include "base_cs_grenade.h"

#include "../shared/cs_weapon_parse.h"

#include "../../cheat/globals/globals.h"

struct cs_weapon_info {

	char _pad0[ 0x14 ];
	int m_max_clip1;
	char _pad1[ 0x70 ]; 
	const char* m_hud_name; 
	const char* m_weapon_name; 
	char _pad2[ 0x38 ]; 
	int m_weapon_type; 
	char _pad3[ 0x40 ];
	float m_range;
};

struct weapon_cs_base : base_combat_character, base_cs_grenade {

	auto& get_ammo( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_WeaponCSBase->m_iClip1" ) ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto& get_view_model_index( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_WeaponCSBase->m_nViewModelIndex" ) ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto is_burst_mode( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_WeaponCSBase->m_bBurstMode" ) ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto get_burst_shots_remaining( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_WeaponCSBase->m_iBurstShotsRemaining" ) ) ];

		return *reinterpret_cast< int* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto get_postpone_fire_ready_time( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_WeaponCSBase->m_flPostponeFireReadyTime" ) ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}
	
	auto get_max_speed( ) {

		return m_memory.get_v_func< float( __thiscall* )( void* ) >( this, 441 )( this );

	}

	auto get_cs_wpn_data( ) {

		return m_memory.get_v_func< cs_weapon_info* ( __thiscall* )( void* ) >( this, 460 )( this ); 

	}

	auto is_gun( ) {

		switch ( get_cs_wpn_data( )->m_weapon_type ) {
			
			case weapon_type_pistol:
			case weapon_type_submachinegun:
			case weapon_type_rifle:
			case weapon_type_shotgun:
			case weapon_type_sniper:
			case weapon_type_machinegun:
				return true;
			
			default: 
				break;
			
		}

		return false;

	}

	auto can_shoot( ) {

		if ( !this->is_gun( ) )
			return false;
		
		return true;
		
		/* if ( !m_globals.m_weapon.is_gun || get_ammo( ) <= 0 || m_globals.m_local_player.pointer->get_next_attack( ) > m_globals.m_server.time )
			return false;
		
		if ( ( m_globals.m_weapon.item_definition_index == weapon_id_famas || m_globals.m_weapon.item_definition_index == weapon_id_glock ) &&
			is_burst_mode( ) && get_burst_shots_remaining( ) > 0 )
			return true;
		
		if ( m_globals.m_weapon.base_combat_character->get_next_primary_attack( ) > m_globals.test )
			return false;
			
		if ( m_globals.m_weapon.item_definition_index == weapon_id_revolver && get_postpone_fire_ready_time( ) > m_globals.m_server.time )
			return false;
		
		return true;*/
		
	}

};