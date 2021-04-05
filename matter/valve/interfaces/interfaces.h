#pragma once

#include "../cdll_int.h"
#include "../vgui/surface.h"
#include "../client_entity_list.h"
#include "../engine/debug_overlay.h"
#include "../global_vars_base.h"
#include "../tier1/interface.h"
#include "../tier1/localize.h"
#include "../data_cache/mdl_cache.h"
#include "../material_system/material_system.h"
#include "../client/net_graph_panel.h"
#include "../input_system/input_system.h"
#include "../shared/cs_gamerules.h"
#include "../engine/client.h"
#include "../tier0/mem_alloc.h"

#include "../../other/hash/hash.h"
#include "../../other/pe/pe.h"
#include "../../other/console/console.h"

#include <string>

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

private:

	template< class t > static t get( const module_info the_module, const std::string_view interface_name ) {
		
		static auto fn_hash = m_hash.get( "CreateInterface" );

		const auto create_interface = m_pe.export_fn( the_module.get_module( ), fn_hash );
		if ( !create_interface )
			return t( );

		auto create_interface_fn = address( create_interface ).add( 0x4 ).relative( );
		if ( !create_interface_fn )
			return t( );

		auto interface_node = create_interface_fn.add( 0x6 ).get< interface_reg* >( 2 );

		while ( interface_node != nullptr ) {

			std::string name = interface_node->m_name;

			if ( !name.compare( 0u, interface_name.length( ), interface_name )  && std::atoi( interface_node->m_name + interface_name.length( ) ) > 0 ) {

				auto interface_address = interface_node->m_create_fn( );
				if ( !interface_address )
					return t( );

				m_console.log( "found interface %s -> 0x%x", interface_node->m_name, interface_address );

				return static_cast< t >( interface_address);

			}

			interface_node = interface_node->m_next;

		}

		return t( );

	}

};

inline interfaces m_interfaces;