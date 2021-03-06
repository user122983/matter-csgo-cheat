#include "modules.h"

#include "../../other/xorstr/xorstr.h"

bool modules::setup( ) {

	if ( !get( ) )
		return false;

	get_addresses( );

	if ( !got_addresses( ) )
		return false;

	return true;

}

bool modules::get( ) {

	m_client_dll = m_pe.get( xorstr_( "client.dll" ) );
	if ( !m_client_dll.get_module( ) )
		return false;

	m_engine_dll = m_pe.get( xorstr_( "engine.dll" ) );
	if ( !m_engine_dll.get_module( ) )
		return false;

	m_server_dll = m_pe.get( xorstr_( "server.dll" ) );
	if ( !m_server_dll.get_module( ) )
		return false;

	m_gameoverlayrenderer_dll = m_pe.get( xorstr_( "gameoverlayrenderer.dll" ) );
	if ( !m_gameoverlayrenderer_dll.get_module( ) )
		return false;

	m_vgui2_dll = m_pe.get( xorstr_( "vgui2.dll" ) );
	if ( !m_vgui2_dll.get_module( ) )
		return false;

	m_vguimatsurface_dll = m_pe.get( xorstr_( "vguimatsurface.dll" ) );
	if ( !m_vguimatsurface_dll.get_module( ) )
		return false;

	m_studiorender_dll = m_pe.get( xorstr_( "studiorender.dll" ) );
	if ( !m_studiorender_dll.get_module( ) )
		return false;

	m_localize_dll = m_pe.get( xorstr_( "localize.dll" ) );
	if ( !m_localize_dll.get_module( ) )
		return false;

	m_datacache_dll = m_pe.get( xorstr_( "datacache.dll" ) );
	if ( !m_datacache_dll.get_module( ) )
		return false;

	m_materialsystem_dll = m_pe.get( xorstr_( "materialsystem.dll" ) );
	if ( !m_materialsystem_dll.get_module( ) )
		return false;

	m_tier0 = m_pe.get( xorstr_( "tier0.dll" ) );
	if ( !m_tier0.get_module( ) )
		return false;

	m_inputsystem_dll = m_pe.get( xorstr_( "inputsystem.dll" ) );
	if ( !m_inputsystem_dll.get_module( ) )
		return false;

	m_filesystem_stdio_dll = m_pe.get( xorstr_( "filesystem_stdio.dll" ) );
	if ( !m_filesystem_stdio_dll.get_module( ) )
		return false;

	m_vstdlib_dll = m_pe.get( xorstr_( "vstdlib.dll" ) );
	if ( !m_vstdlib_dll.get_module( ) )
		return false;
	
	return true;

}

void modules::get_addresses( ) {

	m_client_dll.add_address( xorstr_( "CCSGameRulesProxy::CGameRulesProxy" ), xorstr_( "A1 ? ? ? ? 85 C0 0F 84 ? ? ? ? 80 B8 ? ? ? ? ? 74 7A" ) );
	
	m_client_dll.add_address( xorstr_( "g_pNetGraphPanel" ), xorstr_( "89 1D ? ? ? ? 8B C3" ) );
	m_client_dll.add_address( xorstr_( "g_pMoveData" ), xorstr_( "FF 35 ? ? ? ? 56 85 DB" ) );
	
	m_client_dll.add_address( xorstr_( "IMoveHelper" ), xorstr_( "8B 0D ? ? ? ? 8B 45 ? 51 8B D4 89 02 8B 01" ) );

	m_client_dll.add_address( xorstr_( "C_BaseAnimating::LookupBone" ), xorstr_( "E8 ? ? ? ? 89 44 24 5C" ), true );
	m_client_dll.add_address( xorstr_( "C_BaseAnimating::GetBonePosition" ), xorstr_( "E8 ? ? ? ? 8D 14 24" ), true );
	m_client_dll.add_address( xorstr_( "C_BaseAnimating::GetModelPtr" ), xorstr_( "E8 ? ? ? ? 8B 55 38" ), true );
	m_client_dll.add_address( xorstr_( "C_BaseAnimating::GetFirstSequenceAnimTag" ), xorstr_( "E8 ? ? ? ? F3 0F 11 86 ? ? ? ? 0F 57 DB" ), true );
	m_client_dll.add_address( xorstr_( "C_BaseAnimating::LookupPoseParameter" ), xorstr_( "E8 ? ? ? ? 85 C0 79 08" ), true );
	m_client_dll.add_address( xorstr_( "C_BaseAnimating::GetSequenceActivity" ), xorstr_( "E8 ? ? ? ? 33 C9 3B F0" ), true );
	m_client_dll.add_address( xorstr_( "Studio_SetPoseParameter" ), xorstr_( "E8 ? ? ? ? 0F 28 D8 83 C4 04" ), true );

	m_client_dll.add_address( xorstr_( "C_BaseEntity->m_vecAbsVelocity" ), xorstr_( "F3 0F 10 A6 ? ? ? ? F3 0F 11 64 24 ?" ) );
	m_client_dll.add_address( xorstr_( "C_BaseEntity->m_nAnimOverlay" ), xorstr_( "8B 80 ? ? ? ? 03 C1 74 15" ) );
	m_client_dll.add_address( xorstr_( "C_BaseEntity->m_nPredictionRandomSeed" ), xorstr_( "8B 47 40 A3 ? ? ? ?" ) );
	m_client_dll.add_address( xorstr_( "C_BaseEntity->m_pPredictionPlayer" ), xorstr_( "0F 5B C0 89 35 ? ? ? ?" ) );
	m_client_dll.add_address( xorstr_( "C_BaseEntity::GetGroundEntity" ), xorstr_( "E8 ? ? ? ? 8B 4C 24 14 85 C0" ), true );
	m_client_dll.add_address( xorstr_( "C_BaseEntity::InvalidatePhysicsRecursive" ), xorstr_( "E8 ? ? ? ? 89 5E 18" ), true );
	m_client_dll.add_address( xorstr_( "C_BaseEntity::SetAbsAngles" ), xorstr_( "E8 ? ? ? ? 53 8D 45 F0" ), true );
	m_client_dll.add_address( xorstr_( "C_BaseEntity::CalcAbsoluteVelocity" ), xorstr_( "E8 ? ? ? ? 83 7B 30 00" ), true );
	m_client_dll.add_address( xorstr_( "C_BaseEntity::PhysicsRunThink" ), xorstr_( "E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? F3 0F 10 86 ? ? ? ?" ), true );
	m_client_dll.add_address( xorstr_( "C_BaseEntity::CheckHasThinkFunction" ), xorstr_( "E8 ? ? ? ? EB 11 8B 86 ? ? ? ?" ), true );
	m_client_dll.add_address( xorstr_( "C_BaseEntity::SetAbsOrigin" ), xorstr_( "55 8B EC 83 E4 F8 51 53 56 57 8B F1" ) );

	m_client_dll.add_address( xorstr_( "C_BasePlayer->m_LastCmd" ), xorstr_( "8D 8E ? ? ? ? 89 5C 24 3C" ) );
	m_client_dll.add_address( xorstr_( "C_BasePlayer->m_afButtonForced" ), xorstr_( "8B 86 ? ? ? ? 09 47 30" ) );
	m_client_dll.add_address( xorstr_( "C_BasePlayer->m_afButtonLast" ), xorstr_( "33 CA 89 86 ? ? ? ?" ) );
	m_client_dll.add_address( xorstr_( "C_BasePlayer::GetViewModel" ), xorstr_( "E8 ? ? ? ? 8B F8 8B 47 04" ), true );
	m_client_dll.add_address( xorstr_( "C_BasePlayer::IsLocalPlayer" ), xorstr_( "56 8B F1 85 F6 74 16" ) );

	m_client_dll.add_address( xorstr_( "C_CSPlayer->m_PlayerAnimStateCSGO" ), xorstr_( "8B 8E ? ? ? ? EB 39" ) );
	m_client_dll.add_address( xorstr_( "C_CSPlayer->m_bUseNewAnimstate" ), xorstr_( "80 BE ? ? ? ? ? 74 36 8B 06" ) );
	m_client_dll.add_address( xorstr_( "C_CSPlayer->m_flSpawnTime" ), xorstr_( "89 87 ? ? ? ? 89 B7 ? ? ? ? 89" ) );

	m_client_dll.add_address( xorstr_( "C_CSPlayer::UpdateClientSideAnimation" ), xorstr_( "55 8B EC 51 56 8B F1 80 BE ? ? ? ? ? 74 36" ) );
	m_client_dll.add_address( xorstr_( "C_CSPlayer::HandleTaserAnimation" ), xorstr_( "E8 ? ? ? ? 8B 06 8B CE 8B 80 ? ? ? ? FF D0 84 C0 0F 84 ? ? ? ?" ), true );
	m_client_dll.add_address( xorstr_( "C_CSPlayer::HasC4" ), xorstr_( "56 8B F1 85 F6 74 31 8B 06 8B 80 ? ? ? ? FF D0 84 C0 74 ?" ) );

	m_client_dll.add_address( xorstr_( "CHLClient::LevelShutdown" ), xorstr_( "55 8B EC 83 E4 F8 83 EC 30 C6 05 ? ? ? ? ?" ) );

	m_client_dll.add_address( xorstr_( "ClientModeShared::CreateMove" ), xorstr_( "55 8B EC 8B 0D ? ? ? ? 85 C9 75 06" ) );
	m_client_dll.add_address( xorstr_( "ClientModeShared::GetViewModelFOV" ), xorstr_( "55 8B EC 8B 0D ? ? ? ? 83 EC 08 57" ) );
	m_client_dll.add_address( xorstr_( "ClientModeShared::OverrideView" ), xorstr_( "55 8B EC 83 E4 F8 83 EC 58 56 57 8B 3D ? ? ? ?" ) );

	m_client_dll.add_address( xorstr_( "C_WeaponCSBase::DrawCrosshair" ), xorstr_( "55 8B EC 83 E4 F0 83 EC 78 56 8B F1 8B 0D ? ? ? ?" ) );

	m_client_dll.add_address( xorstr_( "CCSGOPlayerAnimState::Update" ), xorstr_( "E8 ? ? ? ? E9 ? ? ? ? 83 BE ? ? ? ? ?" ), true );
	m_client_dll.add_address( xorstr_( "CCSGOPlayerAnimState::ModifyEyePosition" ), xorstr_( "E8 ? ? ? ? 8B 06 8B CE FF 90 ? ? ? ? 85 C0 74 50" ), true );
	m_client_dll.add_address( xorstr_( "CCSGOPlayerAnimState::DoProceduralFootPlant" ), xorstr_( "E8 ? ? ? ? F6 86 ? ? ? ? ? 0F 84 ? ? ? ?" ), true );
	m_client_dll.add_address( xorstr_( "CCSGOPlayerAnimState::SetUpVelocity" ), xorstr_( "55 8B EC 83 E4 F8 83 EC 30 56 57 8B 3D ? ? ? ?" ) );
	m_client_dll.add_address( xorstr_( "CCSGOPlayerAnimState::SetUpMovement" ), xorstr_( "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60" ), true );
	m_client_dll.add_address( xorstr_( "CCSGOPlayerAnimState::SetUpAimMatrix" ), xorstr_( "55 8B EC 81 EC ? ? ? ? 53 56 57 8B 3D ? ? ? ?" ) );
	m_client_dll.add_address( xorstr_( "CCSGOPlayerAnimState::SetUpWeaponAction" ), xorstr_( "55 8B EC 51 53 56 57 8B F9 8B 77 60" ) );
	m_client_dll.add_address( xorstr_( "CCSGOPlayerAnimState::SetUpMovement" ), xorstr_( "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60" ), true );
	m_client_dll.add_address( xorstr_( "CCSGOPlayerAnimState::SetUpAliveloop" ), xorstr_( "E8 ? ? ? ? 8B CF E8 ? ? ? ? 8B 47 60" ), true );
	m_client_dll.add_address( xorstr_( "CCSGOPlayerAnimState::SetUpWholeBodyAction" ), xorstr_( "E8 ? ? ? ? 8B 47 60 83 B8 ? ? ? ? ?" ), true );
	m_client_dll.add_address( xorstr_( "CCSGOPlayerAnimState::SetUpFlinch" ), xorstr_( "E8 ? ? ? ? 8B CF E8 ? ? ? ? 33 C0" ), true );
	m_client_dll.add_address( xorstr_( "CCSGOPlayerAnimState::SetUpLean" ), xorstr_( "E8 ? ? ? ? 33 C0 89 44 24 0C" ), true );
	m_client_dll.add_address( xorstr_( "CCSGOPlayerAnimState::CacheSequences" ), xorstr_( "E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 8B 77 60" ), true );
	m_client_dll.add_address( xorstr_( "CCSGOPlayerAnimState::IncrementLayerCycle" ), xorstr_( "E8 ? ? ? ? FF 76 60 F3 0F 10 54 24 ?" ), true );
	m_client_dll.add_address( xorstr_( "CCSGOPlayerAnimState::IncrementLayerWeight" ), xorstr_( "E8 ? ? ? ? 8B 5F 60 83 BB ? ? ? ? ?" ), true );

	m_client_dll.add_address( xorstr_( "CStudioHdr::pSeqdesc" ), xorstr_( "E8 ? ? ? ? 03 40 04" ), true );

	m_client_dll.add_address( xorstr_( "CInput::CAM_Think" ), xorstr_( "55 8B EC 83 E4 F8 81 EC ? ? ? ? 56 8B F1 8B 0D ? ? ? ? 57 85 C9" ) );
	m_client_dll.add_address( xorstr_( "CInput::CAM_ToThirdPerson" ), xorstr_("55 8B EC 83 EC 0C 8D 55 F4" ) );

	m_client_dll.add_address( xorstr_( "C_BaseViewModel::UpdateAllViewmodelAddons" ), xorstr_( "E8 ? ? ? ? 8B 16 8B CE 6A 20" ), true );
	m_client_dll.add_address( xorstr_( "C_BaseViewModel::RemoveViewmodelArmModels" ), xorstr_( "E8 ? ? ? ? 46 83 FE 03 7C E7 85 DB" ), true );
	m_client_dll.add_address( xorstr_( "C_BaseViewModel::RemoveViewmodelLabel" ), xorstr_( "E8 ? ? ? ? 8B CB E8 ? ? ? ? 8B CB E8 ? ? ? ? 5F" ), true );
	m_client_dll.add_address( xorstr_( "C_BaseViewModel::RemoveViewmodelStatTrak" ), xorstr_( "E8 ? ? ? ? 56 FF 74 24 10" ), true );
	m_client_dll.add_address( xorstr_( "C_BaseViewModel::RemoveViewmodelStickers" ), xorstr_( "E8 ? ? ? ? 43 83 FB 03 7C CC" ), true );

	m_client_dll.add_address( xorstr_( "CPrediction::RunCommand" ), xorstr_( "55 8B EC 83 E4 C0 83 EC 34 53 56 8B 75 08" ) );

	m_client_dll.add_address( xorstr_( "CClientLeafSystem::InsertIntoTree" ), xorstr_( "56 52 FF 50 18" ) );

	m_client_dll.add_address( xorstr_( "CBaseEntity::EmitSound" ), xorstr_( "55 8B EC 83 EC 4C 53 8B D9 8B" ) );

	m_engine_dll.add_address( xorstr_( "CEngineVGui::Paint" ), xorstr_( "55 8B EC 83 EC 40 53 8B D9 8B 0D ? ? ? ? 89 5D F8" ) );

	m_engine_dll.add_address( xorstr_( "CL_SendMove" ), xorstr_( "E8 ? ? ? ? 84 DB 0F 84 ? ? ? ? 8B 8F ? ? ? ?" ), true );
	m_engine_dll.add_address( xorstr_( "CL_Move" ), xorstr_( "55 8B EC 81 EC ? ? ? ? 53 56 57 8B 3D ? ? ? ? 8A" ) );

	m_engine_dll.add_address( xorstr_( "CCLCMsg_Move::set_data" ), xorstr_( "E8 ? ? ? ? 8D 7E 18" ), true );
	m_engine_dll.add_address( xorstr_( "CCLCMsg_Move::Deconstuctor" ), xorstr_( "E8 ? ? ? ? 5F 5E 5B 8B E5 5D C3 CC CC CC CC CC CC CC CC CC CC CC CC CC 55 8B EC 81 EC ? ? ? ?" ), true );

	m_engine_dll.add_address( xorstr_( "CClientState::CheckFileCRCsWithServer" ), xorstr_( "55 8B EC 81 EC ? ? ? ? 53 8B D9 89 5D F8 80" ) );

	m_engine_dll.add_address(xorstr_( "CEngineBSPTree::ListLeavesInBox" ), xorstr_( "55 8B EC 83 EC 18 8B 4D 0C" ) );

	m_vguimatsurface_dll.add_address( xorstr_( "CMatSystemSurface::StartDrawing" ), xorstr_( "55 8B EC 83 E4 C0 83 EC 38" ) );
	m_vguimatsurface_dll.add_address( xorstr_( "CMatSystemSurface::FinishDrawing" ), xorstr_( "8B 0D ? ? ? ? 56 C6 05 ? ? ? ? ?" ) );
	m_vguimatsurface_dll.add_address( xorstr_( "CMatSystemSurface::LockCursor" ), xorstr_( "80 3D ? ? ? ? ? 8B 91 ? ? ? ? 8B 0D ? ? ? ? C6 05 ? ? ? ? ? 8B 01 74 0B FF 35 ? ? ? ? 52 FF 50 34 C3 6A 00 52 FF 50 34 C3 55" ) );

	m_vgui2_dll.add_address( xorstr_( "CSchemeManager::ReloadSchemes" ), xorstr_( "55 8B EC 83 EC 08 53 56 8B F1 6A 00" ) );

	m_studiorender_dll.add_address( xorstr_( "CStudioRenderContext::DrawModel" ), xorstr_( "55 8B EC 83 E4 F8 83 EC 54" ) );
	 
	m_gameoverlayrenderer_dll.add_address( xorstr_( "GameOverlayRenderer::HookFunc" ), xorstr_( "55 8B EC 51 8B 45 10 C7" ) );
	m_gameoverlayrenderer_dll.add_address( xorstr_( "GameOverlayRenderer::UnhookFunc" ), xorstr_( "E8 ? ? ? ? 83 C4 08 FF 15 ? ? ? ?" ), true );

	m_server_dll.add_address( xorstr_( "CBaseAnimating::DrawServerHitboxes" ), xorstr_( "E8 ? ? ? ? F6 83 ? ? ? ? ? 0F 84 ? ? ? ? 33 FF" ), true );
	m_server_dll.add_address( xorstr_( "UTIL_PlayerByIndex" ), xorstr_( "85 C9 7E 32 A1 ? ? ? ?" ) );
	m_server_dll.add_address( xorstr_( "CCSGOPlayerAnimState::SetUpVelocity" ), xorstr_( "55 8B EC 83 E4 F8 83 EC 28 56 57 8B 3D ? ? ? ? 8B F1 8B CF" ) );
	
}

bool modules::got_addresses( ) {

	if ( !m_client_dll.valid_addresses( ) )
		return false;

	if ( !m_engine_dll.valid_addresses( ) )
		return false;

	if ( !m_server_dll.valid_addresses( ) )
		return false;

	if ( !m_gameoverlayrenderer_dll.valid_addresses( ) )
		return false;

	if ( !m_vgui2_dll.valid_addresses( ) )
		return false;

	if ( !m_vguimatsurface_dll.valid_addresses( ) )
		return false;

	if ( !m_studiorender_dll.valid_addresses( ) )
		return false;

	if ( !m_localize_dll.valid_addresses( ) )
		return false;

	if ( !m_datacache_dll.valid_addresses( ) )
		return false;

	if ( !m_materialsystem_dll.valid_addresses( ) )
		return false;

	if ( !m_tier0.valid_addresses( ) )
		return false;

	if ( !m_filesystem_stdio_dll.valid_addresses( ) )
		return false;

	if ( !m_vstdlib_dll.valid_addresses( ) )
		return false;
	
	return true;

}