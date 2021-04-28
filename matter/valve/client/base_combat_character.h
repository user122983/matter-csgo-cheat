#pragma once

#include "base_entity.h"

struct base_combat_character : base_entity {

	auto get_active_weapon( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_BaseCombatCharacter->m_hActiveWeapon" ) ) ];

		return *reinterpret_cast< std::size_t* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto get_next_attack( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_BaseCombatCharacter->m_flNextAttack" ) ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}
	
	auto get_item_definition_index( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_BaseAttributableItem->m_iItemDefinitionIndex" ) ) ];

		return *reinterpret_cast< short* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto get_next_primary_attack( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_BaseCombatWeapon->m_flNextPrimaryAttack" ) ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto get_next_secondary_attack( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_BaseCombatWeapon->m_flNextSecondaryAttack" ) ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

};
