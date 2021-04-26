#include "interfaces.h"

bool interfaces::setup( ) {

	m_client = get< base_client_dll* >( m_modules.m_client_dll, xorstr_( "VClient" ) );
	if ( !m_client )
		return false;

	m_surface = get< surface* >( m_modules.m_vguimatsurface_dll, xorstr_( "VGUI_Surface" ) );
	if ( !m_surface )
		return false;

	m_entity_list = get< client_entity_list* >( m_modules.m_client_dll, xorstr_( "VClientEntityList" ) );
	if ( !m_entity_list )
		return false;

	m_engine_trace = get< engine_trace* >( m_modules.m_engine_dll, xorstr_( "EngineTraceClient" ) );
	if ( !m_engine_trace )
		return false;

	m_debug_overlay = get< debug_overlay* >( m_modules.m_engine_dll, xorstr_( "VDebugOverlay" ) );
	if ( !m_debug_overlay )
		return false;

	m_globals = m_memory.get_v_func( m_client, 11 ).add( 0xa ).get< global_vars_base* >( 2 );
	if ( !m_globals )
		return false;

	m_console.log( xorstr_( "found pointer gpGlobals -> 0x%x" ), m_globals );

	m_engine = get< engine_client* >( m_modules.m_engine_dll, xorstr_( "VEngineClient" ) );
	if ( !m_engine )
		return false;

	m_localize = get< localize* >( m_modules.m_localize_dll, xorstr_( "Localize_" ) );
	if ( !m_localize )
		return false;

	m_mdl_cache = get< mdl_cache* >( m_modules.m_datacache_dll, xorstr_( "MDLCache" ) );
	if ( !m_mdl_cache )
		return false;

	m_material_system = get< material_system* >( m_modules.m_materialsystem_dll, xorstr_( "VMaterialSystem" ) );
	if ( !m_material_system )
		return false;

	m_net_graph_panel = m_modules.m_client_dll.get_address( xorstr_( "g_pNetGraphPanel" ) ).add( 0x2 ).get< net_graph_panel* >( 2 );
	if ( !m_net_graph_panel )
		return false;

	m_console.log( xorstr_( "found pointer g_pNetGraphPanel -> 0x%x" ), m_net_graph_panel );

	m_client_state = m_memory.get_v_func( m_engine, 12 ).add( 0x10 ).get< client_state* >( 2 );
	if ( !m_client_state )
		return false;

	m_console.log( xorstr_( "found reference to GetBaseLocalClient -> 0x%x" ), m_client_state );

	m_mem_alloc = *reinterpret_cast< mem_alloc** >( m_pe.export_fn( m_modules.m_tier0.get_module( ), m_hash.get( xorstr_( "g_pMemAlloc" ) ) ) );
	if ( !m_mem_alloc )
		return false;

	m_console.log( xorstr_( "found pointer g_pMemAlloc -> 0x%x" ), m_mem_alloc );
	 
	m_input_system = get< input_system* >( m_modules.m_inputsystem_dll, xorstr_( "InputSystemVersion" ) );
	if ( !m_input_system )
		return false;
	
	m_game_movement = get< game_movement* >( m_modules.m_client_dll, xorstr_( "GameMovement" ) );
	if ( !m_game_movement )
		return false;

	m_move_data = m_modules.m_client_dll.get_address( xorstr_( "g_pMoveData" ) ).add( 0x2 ).get< move_data* >( 2 );
	if ( !m_move_data )
		return false;

	m_console.log( xorstr_( "found pointer g_pMoveData -> 0x%x" ), m_move_data );

	m_file_system = get< file_system* >( m_modules.m_filesystem_stdio_dll, xorstr_( "VFileSystem" ) );
	if ( !m_file_system )
		return false;

	m_engine_sound = get< engine_sound* >( m_modules.m_engine_dll, xorstr_( "IEngineSoundClient" ) );
	if ( !m_engine_sound )
		return false;

	m_prediction = get< prediction* >( m_modules.m_client_dll, xorstr_( "VClientPrediction" ) );
	if ( !m_prediction )
		return false;

	m_convar = get< convar* >( m_modules.m_vstdlib_dll, xorstr_( "VEngineCvar" ) );
	if ( !m_convar )
		return false;

	return true;

}
