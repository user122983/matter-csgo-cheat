#include "signatures.h"

bool signatures::setup( ) {

	// module names

	m_client_dll = m_pe.get( "client.dll" );
	m_engine_dll = m_pe.get( "engine.dll" );
	m_server_dll = m_pe.get( "server.dll" );
	m_gameoverlayrenderer_dll = m_pe.get( "gameoverlayrenderer.dll" );
	m_vgui2_dll = m_pe.get( "vgui2.dll" );
	m_vguimatsurface_dll = m_pe.get( "vguimatsurface.dll" );
	m_studiorender_dll = m_pe.get( "studiorender.dll" );
	m_localize_dll = m_pe.get( "localize.dll" );
	m_datacache_dll = m_pe.get( "datacache.dll" );
	m_materialsystem_dll = m_pe.get( "materialsystem.dll" );
	m_inputsystem_dll = m_pe.get( "inputsystem.dll" );
	m_tier0 = m_pe.get( "tier0.dll" );
	
	// offsets

	m_anim_overlay = m_client_dll.find_pattern( "8B 80 ? ? ? ? 03 C1 74 15" );
	m_abs_velocity = m_client_dll.find_pattern( "F3 0F 10 A6 ? ? ? ? F3 0F 11 64 24 ?" );
	m_player_anim_state_csgo = m_client_dll.find_pattern( "8B 8E ? ? ? ? EB 39" );

	// functions

	m_level_shutdown = m_client_dll.find_pattern( "55 8B EC 83 E4 F8 83 EC 30 C6 05 ? ? ? ? ?" );
	m_create_move = m_client_dll.find_pattern( "55 8B EC 8B 0D ? ? ? ? 85 C9 75 06" );
	m_override_view = m_client_dll.find_pattern( "55 8B EC 83 E4 F8 83 EC 58 56 57 8B 3D ? ? ? ?" );
	m_get_view_model_fov = m_client_dll.find_pattern( "55 8B EC 8B 0D ? ? ? ? 83 EC 08 57" );
	m_draw_crosshair = m_client_dll.find_pattern( "55 8B EC 83 E4 F0 83 EC 78 56 8B F1 8B 0D ? ? ? ?" );
	m_update = m_client_dll.find_pattern( "E8 ? ? ? ? E9 ? ? ? ? 83 BE ? ? ? ? ?" ).relative( );
	m_modify_eye_position = m_client_dll.find_pattern( "E8 ? ? ? ? 8B 06 8B CE FF 90 ? ? ? ? 85 C0 74 50" ).relative( );
	m_do_procedural_foot_plant = m_client_dll.find_pattern( "E8 ? ? ? ? F6 86 ? ? ? ? ? 0F 84 ? ? ? ?" ).relative( );
	m_setup_velocity = m_client_dll.find_pattern( "55 8B EC 83 E4 F8 83 EC 30 56 57 8B 3D ? ? ? ?" );
	m_setup_movement = m_client_dll.find_pattern( "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60" ).relative( );
	m_setup_aim_matrix = m_client_dll.find_pattern( "55 8B EC 81 EC ? ? ? ? 53 56 57 8B 3D ? ? ? ?" );
	m_set_up_weapon_action = m_client_dll.find_pattern( "55 8B EC 51 53 56 57 8B F9 8B 77 60" );
	m_set_up_movement = m_client_dll.find_pattern( "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60" ).relative( );
	m_set_up_alive_loop = m_client_dll.find_pattern( "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60" ).relative( );
	m_set_up_whole_body_action = m_client_dll.find_pattern( "E8 ? ? ? ? 8B 47 60 83 B8 ? ? ? ? ?" ).relative( );
	m_set_up_flinch = m_client_dll.find_pattern( "E8 ? ? ? ? 8B CF E8 ? ? ? ? 33 C0" ).relative( );
	m_set_up_lean = m_client_dll.find_pattern( "E8 ? ? ? ? 33 C0 89 44 24 0C" ).relative( );
	m_cache_sequences = m_client_dll.find_pattern( "E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 8B 77 60" ).relative( );
	m_get_ground_entity = m_client_dll.find_pattern( "E8 ? ? ? ? 8B 4C 24 14 85 C0" ).relative( );
	m_invalidate_physics_recursive = m_client_dll.find_pattern( "E8 ? ? ? ? 89 5E 18" ).relative( );
	m_set_abs_angles = m_client_dll.find_pattern( "E8 ? ? ? ? 53 8D 45 F0" ).relative( );
	m_lookup_bone = m_client_dll.find_pattern( "E8 ? ? ? ? 89 44 24 5C" ).relative( );
	m_get_bone_position = m_client_dll.find_pattern( "E8 ? ? ? ? 8D 14 24" ).relative( );
	m_calc_absolute_velocity = m_client_dll.find_pattern( "E8 ? ? ? ? 83 7B 30 00" ).relative( );
	m_increment_layer_cycle = m_client_dll.find_pattern( "E8 ? ? ? ? FF 76 60 F3 0F 10 54 24 ?" ).relative( );
	m_increment_layer_weight = m_client_dll.find_pattern( "E8 ? ? ? ? 8B 5F 60 83 BB ? ? ? ? ?" ).relative( );
	m_get_model_ptr = m_client_dll.find_pattern( "E8 ? ? ? ? 8B 55 38" ).relative( );
	m_get_first_sequence_anim_tag = m_client_dll.find_pattern( "E8 ? ? ? ? F3 0F 11 86 ? ? ? ? 0F 57 DB" ).relative( );
	m_seqdesc = m_client_dll.find_pattern( "E8 ? ? ? ? 03 40 04" ).relative( );
	m_lookup_pose_parameter = m_client_dll.find_pattern( "E8 ? ? ? ? 85 C0 79 08" ).relative( );
	m_studio_set_pose_parameter = m_client_dll.find_pattern( "E8 ? ? ? ? 0F 28 D8 83 C4 04" ).relative( );
	m_cam_think = m_client_dll.find_pattern( "55 8B EC 83 E4 F8 81 EC ? ? ? ? 56 8B F1 8B 0D ? ? ? ? 57 85 C9" );
	m_cam_to_third_person = m_client_dll.find_pattern( "55 8B EC 83 EC 0C 8D 55 F4" );
	m_has_c4 = m_client_dll.find_pattern( "56 8B F1 85 F6 74 31 8B 06 8B 80 ? ? ? ? FF D0 84 C0 74 ?" );
	m_get_sequence_activity = m_client_dll.find_pattern( "E8 ? ? ? ? 33 C9 3B F0" ).relative( );
	m_set_abs_origin = m_client_dll.find_pattern( "55 8B EC 83 E4 F8 51 53 56 57 8B F1" );
	m_emit_sound = m_client_dll.find_pattern( "55 8B EC 83 EC 4C 53 8B D9 8B" );

	m_paint = m_engine_dll.find_pattern( "55 8B EC 83 EC 40 53 8B D9 8B 0D ? ? ? ? 89 5D F8" );
	m_cl_send_move = m_engine_dll.find_pattern( "E8 ? ? ? ? 84 DB 0F 84 ? ? ? ? 8B 8F ? ? ? ?" ).relative( );
	m_set_data = m_engine_dll.find_pattern( "E8 ? ? ? ? 8D 7E 18" ).relative( );
	m_cl_msg_move_deconstructor = m_engine_dll.find_pattern( "E8 ? ? ? ? 5F 5E 5B 8B E5 5D C3 CC CC CC CC CC CC CC CC CC CC CC CC CC 55 8B EC 81 EC ? ? ? ?" ).relative( );
	
	m_start_drawing = m_vguimatsurface_dll.find_pattern( "55 8B EC 83 E4 C0 83 EC 38" );
	m_finish_drawing = m_vguimatsurface_dll.find_pattern( "8B 0D ? ? ? ? 56 C6 05 ? ? ? ? ?" );
	m_lock_cursor = m_vguimatsurface_dll.find_pattern( "80 3D ? ? ? ? ? 8B 91 ? ? ? ? 8B 0D ? ? ? ? C6 05 ? ? ? ? ? 8B 01 74 0B FF 35 ? ? ? ? 52 FF 50 34 C3 6A 00 52 FF 50 34 C3 55" );

	m_reload_schemes = m_vgui2_dll.find_pattern( "55 8B EC 83 EC 08 53 56 8B F1 6A 00" );

	m_draw_model = m_studiorender_dll.find_pattern( "55 8B EC 83 E4 F8 83 EC 54" );

	m_hook = m_gameoverlayrenderer_dll.find_pattern( "55 8B EC 51 8B 45 10 C7" );
	m_restore = m_gameoverlayrenderer_dll.find_pattern( "E8 ? ? ? ? 83 C4 08 FF 15 ? ? ? ?" ).relative( );

	m_draw_server_hitboxes = m_server_dll.find_pattern( "E8 ? ? ? ? F6 83 ? ? ? ? ? 0F 84 ? ? ? ? 33 FF" ).relative( );
	m_util_player_by_index = m_server_dll.find_pattern( "85 C9 7E 2A A1 ? ? ? ?" );
	m_server_setup_velocity = m_server_dll.find_pattern( "55 8B EC 83 E4 F8 83 EC 28 56 57 8B 3D ? ? ? ? 8B F1 8B CF" );

	return true;

}