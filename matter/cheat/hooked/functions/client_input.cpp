#include "../hooked.h"

#include "../../input/input.h"

void __fastcall hooked::client_input_fn::cam_think( client_input* ecx, void* edx ) {

	static auto o_cam_think = m_modules.m_client_dll.get< decltype( &cam_think ) >( xorstr_( "CInput::CAM_Think" ) );

	ecx->m_camera_in_third_person = !m_input.is_key_toggled( 0x56, m_globals.m_third_person );

	ecx->m_cam_command = 1;

	return o_cam_think( ecx, edx );

}

void __fastcall hooked::client_input_fn::cam_to_third_person( client_input* ecx, void* edx ) {

	static auto o_cam_to_third_person = m_modules.m_client_dll.get< decltype( &cam_to_third_person ) >( xorstr_( "CInput::CAM_ToThirdPerson" ) );

	o_cam_to_third_person( ecx, edx );

	ecx->m_camera_offset.z = 150;

}