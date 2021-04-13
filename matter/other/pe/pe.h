#pragma once

#include "../hash/hash.h"
#include "../module/module.h"

#include <unordered_map>

// disable cringe warning
#pragma warning(disable : 4244)

struct pe {

	bool setup( );

	std::size_t export_fn( std::size_t base, std::size_t fn_hash, bool in_memory = false );

	std::size_t get( std::string_view name ) {
		
		return m_loaded_modules[ m_hash.get( name ) ];
		
	}

private:

	std::unordered_map< std::size_t, std::size_t > m_loaded_modules;
	
};

inline pe m_pe;
