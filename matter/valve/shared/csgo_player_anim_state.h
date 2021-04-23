#pragma once

struct animstate_pose_param_cache {

	bool m_initialized;
	char _pad0[ 0x3 ]; 
	int m_index; 
	const char* m_name;

	bool init( cs_player* player, const char* pose_param_name ) {

		m_interfaces.m_mdl_cache->begin_lock( );

		m_name = pose_param_name;
		m_index = player->lookup_pose_parameter( pose_param_name );

		if ( m_index != 1 )
			m_initialized = true;

		m_interfaces.m_mdl_cache->end_lock( );

		return m_initialized;

	}

	void set_value( cs_player* player, float value ) {

		if ( !m_initialized )
			init( player, m_name );

		if ( m_initialized && player ) {

			m_interfaces.m_mdl_cache->begin_lock( );

			player->set_pose_parameter( m_index, value );

			m_interfaces.m_mdl_cache->end_lock( );

		}

	}

}; 

struct csgo_player_anim_state {

	auto update( float y, float x ) {

		static auto function = m_modules.m_client_dll.get_address( "CCSGOPlayerAnimState::Update" ).as< void( __vectorcall* )( void*, void*, float, float, float, void* ) >( );
		
		return function( this, nullptr, 0.f, y, x, nullptr );

	}
	
	auto set_up_velocity( ) {

		static auto function = m_modules.m_client_dll.get_address( "CCSGOPlayerAnimState::SetUpVelocity" ).as< void( __thiscall* )( void* ) >( );
		
		return function( this );

	}

	auto set_up_aim_matrix( ) {

		static auto function = m_modules.m_client_dll.get_address( "CCSGOPlayerAnimState::SetUpAimMatrix" ).as< void( __thiscall* )( void* ) >( );
		
		return function( this );

	}

	auto set_up_weapon_action( ) {

		static auto function = m_modules.m_client_dll.get_address( "CCSGOPlayerAnimState::SetUpWeaponAction" ).as< void( __thiscall* )( void* ) >( );
		
		return function( this );

	}

	auto set_up_movement( ) {

		static auto function = m_modules.m_client_dll.get_address( "CCSGOPlayerAnimState::SetUpMovement" ).as< void( __thiscall* )( void* ) >( );
		
		return function( this );

	}

	auto set_up_alive_loop( ) {

		static auto function = m_modules.m_client_dll.get_address( "CCSGOPlayerAnimState::SetUpAliveloop" ).as< void( __thiscall* )( void* ) >( );
		
		return function( this );

	}

	auto set_up_whole_body_action( ) {

		static auto function = m_modules.m_client_dll.get_address( "CCSGOPlayerAnimState::SetUpWholeBodyAction" ).as< void( __thiscall* )( void* ) >( );
		
		return function( this );

	}

	auto set_up_flashed_reaction( ) {

		// todo

	}

	auto set_up_flinch( ) {

		static auto function = m_modules.m_client_dll.get_address( "CCSGOPlayerAnimState::SetUpFlinch" ).as< void( __thiscall* )( void* ) >( );
		
		return function( this );

	}

	auto set_up_lean( ) {

		static auto function = m_modules.m_client_dll.get_address( "CCSGOPlayerAnimState::SetUpLean" ).as< void( __thiscall* )( void* ) >( );
		
		return function( this );

	}

	auto cache_sequences( ) {

		static auto function = m_modules.m_client_dll.get_address( "CCSGOPlayerAnimState::CacheSequences" ).as< bool( __thiscall* )( void* ) >( );
		
		return function( this );

	}

	auto increment_layer_cycle( int layer_index, bool allow_loop ) {

		static auto function = m_modules.m_client_dll.get_address( "CCSGOPlayerAnimState::IncrementLayerCycle" ).as< void( __thiscall* )( void*, int, bool ) >( );
		
		return function( this, layer_index, allow_loop );

	}

	auto increment_layer_weight( int layer_index ) {

		static auto function = m_modules.m_client_dll.get_address( "CCSGOPlayerAnimState::IncrementLayerWeight" ).as< void( __thiscall* )( void*, int ) >( );
		
		return function( this, layer_index );

	}

	char _pad0[ 0x4 ]; 
	bool m_first_run_since_init; 
	char _pad1[ 0x5b ]; 
	cs_player* m_player; 
	weapon_cs_base* m_weapon; 
	weapon_cs_base* m_weapon_last; 
	float m_last_update_time;
	int m_last_update_frame; 
	float m_last_update_increment; 
	float m_eye_yaw; 
	float m_eye_pitch; 
	float m_foot_yaw; 
	float m_foot_yaw_last; 
	float m_move_yaw; 
	float m_move_yaw_ideal; 
	float m_move_yaw_current_to_ideal; 
	float m_time_to_align_lower_body; 
	float m_primary_cycle; 
	float m_move_weight; 
	float m_move_weight_smoothed; 
	float m_anim_duck_amount;
	float m_duck_additional; 
	float m_recrouch_weight; 
	vector_3d m_position_current; 
	vector_3d m_position_last;
	vector_3d m_velocity; 
	vector_3d m_velocity_normalized; 
	vector_3d m_velocity_normalized_non_zero;
	float m_velocity_length_xy; 
	float m_velocity_length_z; 
	float m_speed_as_portion_of_run_top_speed; 
	float m_speed_as_portion_of_walk_top_speed;
	float m_speed_as_portion_of_crouch_top_speed; 
	float m_duration_moving; 
	float m_duration_still; 
	bool m_on_ground; 
	bool m_landing; 
	char _pad2[ 0x12 ]; 
	float m_walk_to_run_transition; 
	char _pad3[ 0x4 ]; 
	float m_in_air_smooth_value; 
	bool m_on_ladder; 
	char _pad4[ 0x3 ]; 
	float m_ladder_weight; 
	char _pad5[ 0x2c ]; 
	vector_3d m_velocity_last; 
	char _pad6[ 0x45 ];
	bool m_player_is_accelerating; 
	char _pad7[ 0x2 ]; 
	animstate_pose_param_cache m_pose_param_mappings[ 20 ]; 
	float m_duration_move_weight_is_too_high; 
	float m_static_approach_speed; 
	int m_previous_move_state;
	float m_stutter_step; 
	char _pad8[ 0x80 ]; 
	float m_aim_yaw_min; 
	float m_aim_yaw_max; 
	float m_aim_pitch_min; 
	float m_aim_pitch_max; 
	int m_animstate_version;

	// custom members

	bool m_adjust_started;
	float m_lower_body_realign_timer;

};