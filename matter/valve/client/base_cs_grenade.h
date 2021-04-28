#pragma once

struct base_cs_grenade {

	auto is_pin_pulled( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_BaseCSGrenade->m_bPinPulled" ) ) ];

		return *reinterpret_cast< bool* >( reinterpret_cast< std::size_t >( this ) + offset );

	}

	auto get_throw_time( ) {

		static auto offset = m_netvars.m_offsets[ m_hash.get( xorstr_( "DT_BaseCSGrenade->m_fThrowTime" ) ) ];

		return *reinterpret_cast< float* >( reinterpret_cast< std::size_t> ( this ) + offset );

	}

};
