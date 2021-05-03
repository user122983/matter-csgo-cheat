#include "hooked.h"

bool hooked::setup( ) {

	// vgui_baseui_fn
	if ( !m_modules.m_engine_dll.hook_function( xorstr_( "CEngineVGui::Paint" ), &vgui_baseui_fn::paint ) )
		return false;
	
	// cdll_client_fn
	if ( !m_modules.m_client_dll.hook_function( xorstr_( "CHLClient::LevelShutdown" ), &cdll_client_fn::level_shutdown ) )
		return false;

	// cl_main_fn
	if ( !m_modules.m_engine_dll.hook_function( xorstr_( "CL_SendMove" ), &cl_main_fn::cl_send_move ) )
		return false;

	if ( !m_modules.m_engine_dll.hook_function( xorstr_( "CL_Move" ), &cl_main_fn::cl_move ) )
		return false;

	// client_input_fn
	if ( !m_modules.m_client_dll.hook_function( xorstr_( "CInput::CAM_Think" ), &client_input_fn::cam_think ) )
		return false;

	if ( !m_modules.m_client_dll.hook_function( xorstr_( "CInput::CAM_ToThirdPerson" ), &client_input_fn::cam_to_third_person ) )
		return false;

	// client_mode_shared_fn
	if ( !m_modules.m_client_dll.hook_function( xorstr_( "ClientModeShared::CreateMove" ), &client_mode_shared_fn::create_move ) )
		return false;

	if ( !m_modules.m_client_dll.hook_function( xorstr_( "ClientModeShared::GetViewModelFOV" ), &client_mode_shared_fn::get_view_model_fov ) )
		return false;

	// cs_player_fn
	if ( !m_modules.m_client_dll.hook_function( xorstr_( "C_CSPlayer::UpdateClientSideAnimation" ), &cs_player_fn::update_client_side_animation ) )
		return false;

	// csgo_player_anim_state_fn
	if ( !m_modules.m_client_dll.hook_function( xorstr_( "CCSGOPlayerAnimState::Update" ), &csgo_player_anim_state_fn::update ) )
		return false;

	if ( !m_modules.m_client_dll.hook_function( xorstr_( "CCSGOPlayerAnimState::ModifyEyePosition" ), &csgo_player_anim_state_fn::modify_eye_position ) )
		return false;

	if ( !m_modules.m_client_dll.hook_function( xorstr_( "CCSGOPlayerAnimState::DoProceduralFootPlant" ), &csgo_player_anim_state_fn::do_procedural_foot_plant ) )
		return false;

	if ( !m_modules.m_client_dll.hook_function( xorstr_( "CCSGOPlayerAnimState::SetUpVelocity" ), &csgo_player_anim_state_fn::set_up_velocity ) )
		return false;

	if ( !m_modules.m_client_dll.hook_function( xorstr_( "CCSGOPlayerAnimState::SetUpMovement" ), &csgo_player_anim_state_fn::set_up_movement ) )
		return false;

	// mat_system_surface_fn
	if ( !m_modules.m_vguimatsurface_dll.hook_function( xorstr_( "CMatSystemSurface::LockCursor" ), &mat_system_surface_fn::lock_cursor ) )
		return false;

	// prediction_fn
	if ( !m_modules.m_client_dll.hook_function( xorstr_( "CPrediction::RunCommand" ), &prediction_fn::run_command ) )
		return false;

	// scheme_manager_fn
	if ( !m_modules.m_vgui2_dll.hook_function( xorstr_( "CSchemeManager::ReloadSchemes" ), &scheme_manager_fn::reload_schemes ) )
		return false;

	// studio_render_fn
	if ( !m_modules.m_studiorender_dll.hook_function( xorstr_( "CStudioRenderContext::DrawModel" ), &studio_render_fn::draw_model ) )
		return false;

	// weapon_cs_base_fn
	if ( !m_modules.m_client_dll.hook_function( xorstr_( "C_WeaponCSBase::DrawCrosshair" ), &weapon_cs_base_fn::draw_crosshair ) )
		return false;

	// client_state_fn
	if ( !m_modules.m_engine_dll.hook_function( xorstr_( "CClientState::CheckFileCRCsWithServer" ), &client_state_fn::check_file_crcs_with_server ) )
		return false;

/*	// engine_bsp_tree_fn
	if ( !m_modules.m_engine_dll.hook_function( xorstr_( "CEngineBSPTree::ListLeavesInBox" ), &engine_bsp_tree_fn::list_leaves_in_box ) )
		return false;*/

	// file_system_fn
	if ( !m_modules.m_engine_dll.hook_function( xorstr_( "IFileSystem::CanLoadThirdPartyFiles" ), &file_system_fn::can_load_third_party_files, m_memory.get_v_func( m_interfaces.m_file_system, 128 ) ) )
		return false;

	// sys_engine_fn
	static convar* engine_no_focus_sleep = m_interfaces.m_convar->find_var( xorstr_( "engine_no_focus_sleep" ) );
	if ( !m_modules.m_engine_dll.hook_function( xorstr_( "engine_no_focus_sleep" ), &sys_engine_fn::engine_no_focus_sleep, m_memory.get_v_func( engine_no_focus_sleep, 11 ) ) )
		return false;

	return true;
	 
}

void hooked::unload( ) {

	m_modules.m_client_dll.unload_functions( );
	m_modules.m_engine_dll.unload_functions( );
	m_modules.m_server_dll.unload_functions( );
	m_modules.m_gameoverlayrenderer_dll.unload_functions( );
	m_modules.m_vgui2_dll.unload_functions( );
	m_modules.m_vguimatsurface_dll.unload_functions( );
	m_modules.m_studiorender_dll.unload_functions( );
	m_modules.m_localize_dll.unload_functions( );
	m_modules.m_datacache_dll.unload_functions( );
	m_modules.m_materialsystem_dll.unload_functions( );
	m_modules.m_tier0.unload_functions( );
	m_modules.m_filesystem_stdio_dll.unload_functions( );
	
}