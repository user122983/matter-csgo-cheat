#pragma once

#include "../engine/cdll_engine_int.h"
#include "../public/vgui/surface.h"
#include "../public/client_entity_list.h"
#include "../engine/debug_overlay.h"
#include "../public/global_vars_base.h"
#include "../tier1/interface.h"
#include "../tier1/localize.h"
#include "../data_cache/mdl_cache.h"
#include "../material_system/material_system.h"
#include "../client/net_graph_panel.h"
#include "../input_system/input_system.h"
#include "../shared/cs_gamerules.h"
#include "../engine/client.h"
#include "../tier0/mem_alloc.h"
#include "../shared/game_movement.h"
#include "../public/file_system.h"
#include "../engine/engine_sound.h"
#include "../client/prediction.h"
#include "../tier1/convar.h"
#include "../engine/engine_trace.h"

#include "../../other/console/console.h"

struct interfaces {

	bool setup( );

	base_client_dll* m_client;
	surface* m_surface;
	client_entity_list* m_entity_list;
	debug_overlay* m_debug_overlay;
	global_vars_base* m_globals;
	engine_client* m_engine;
	localize* m_localize;
	mdl_cache* m_mdl_cache;
	material_system* m_material_system;
	net_graph_panel* m_net_graph_panel;
	input_system* m_input_system;
	cs_game_rules_proxy* m_cs_game_rules_proxy;
	client_state* m_client_state;
	mem_alloc* m_mem_alloc;
	game_movement* m_game_movement;
	move_data* m_move_data;
	file_system* m_file_system;
	engine_sound* m_engine_sound;
	prediction* m_prediction;
	convar* m_convar;
	engine_trace* m_engine_trace;

private:

	template< class t > t get( module_info the_module, std::string_view interface_name ) {
		
		static std::size_t fn_hash = m_hash.get( xorstr_( "CreateInterface" ) );

		std::size_t create_interface = m_pe.export_fn( the_module.get_module( ), fn_hash );
		if ( !create_interface )
			return t( );

		address create_interface_fn = address( create_interface ).add( 0x4 ).relative( );
		if ( !create_interface_fn )
			return t( );

		interface_reg* interface_node = create_interface_fn.add( 0x6 ).get< interface_reg* >( 2 );

		while ( interface_node != nullptr ) {

			std::string name = interface_node->m_name;
			
			if ( !name.compare( 0u, interface_name.length( ), interface_name ) && std::atoi( interface_node->m_name + interface_name.length( ) ) > 0 ) {

				void* interface_address = interface_node->m_create_fn( );
				if ( !interface_address )
					return t( );

				m_console.log( xorstr_( "found interface %s -> 0x%x" ), interface_node->m_name, interface_address );

				return static_cast< t >( interface_address);

			}

			interface_node = interface_node->m_next;

		}

		return t( );

	}

};

inline interfaces m_interfaces;