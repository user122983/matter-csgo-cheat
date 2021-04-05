#include "detour.h"

#include "../signatures/signatures.h"
#include "../../other/console/console.h"

bool detour::setup( const std::string_view name, void* function, void* custom_function ) {

	if ( !function || !custom_function )
		return false;

	auto& info = m_detours[ m_hash.get( name.data( ) ) ];
	info = { function, nullptr };

	const auto hook = m_signatures.m_hook.as< bool( __cdecl* )( void*, void*, void*, int ) >( );
	
	const auto result = hook( info.m_function, custom_function, &info.m_original, 0 );

	if ( !result )
		return false;

	m_console.log( "hooked %s -> 0x%x", name.data( ), function );

	return true;

}

void detour::unload( ) {

	const auto restore = m_signatures.m_restore.as< void( __cdecl* )( void*, bool ) >( );

	for ( auto& [ fst, snd ] : m_detours )
		restore( snd.m_function, false );

}