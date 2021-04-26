#pragma once

#include "../netvars/netvars.h"

#include "../../other/hash/hash.h"

struct cs_game_rules_proxy {

	auto is_freeze_period( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSGameRulesProxy->m_bFreezePeriod" ) ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto is_valve_server( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_CSGameRulesProxy->m_bIsValveDS" ) ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast< std::size_t >( this ) + offset );

	}
	
};
