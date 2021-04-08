#pragma once

#include "../shared/user_cmd.h"
#include "../other/utils/utils.h"

struct base_player;
struct move_helper;
struct move_data;

struct prediction {

	auto check_moving_ground( base_player* player, const double frametime ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, base_player*, double ) >( this, 18 )( this, player, frametime );

	}

	auto setup_move( base_player* player, user_cmd* cmd, move_helper* helper, move_data* move ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, base_player*, user_cmd*, move_helper*, move_data* ) >( this, 20 )( this, player, cmd, helper, move );

	}

	auto finish_move( base_player* player, user_cmd* cmd, move_data* move ) {

		return m_utils.get_v_func< void( __thiscall* )( void*, base_player*, user_cmd*, move_data* ) >( this, 21 )( this, player, cmd, move );

	}

	static auto start_command( base_player* player, user_cmd* cmd ) {

		player->get_current_command( ) = cmd;
		player->get_last_command( ) = *cmd;
		base_entity::set_prediction_random_seed( cmd );
		base_entity::set_prediction_player( player );

	}

	static auto run_pre_think( base_player* player ) {

		if ( !player->physics_run_think( ) )
			return;

		player->pre_think( );

	}

	static auto run_think( base_player* player, double frametime ) {

		const auto thinktick = player->get_next_think_tick( );

		if ( thinktick <= 0 || thinktick > player->get_tick_base( ) )
			return;

		{ /* C_BaseEntity::SetNextThink */
			player->get_next_think_tick( ) = -1;

			player->check_has_think_function( false );
		}

		player->think( );

	}

	static auto run_post_think( base_player* player ) {

		player->post_think( );

	}

	static auto finish_command( base_player* player ) {

		player->get_current_command( ) = nullptr;
		base_entity::set_prediction_random_seed( nullptr );
		base_entity::set_prediction_player( nullptr );

	}

	char _pad0[ 0xa ]; 
	bool m_engine_paused; 

};