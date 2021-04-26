#pragma once

#include "../client/base_animating.h"
#include "../modules/modules.h"

struct base_view_model : base_animating {

	auto update_all_viewmodel_addons( ) {

		static auto function = m_modules.m_client_dll.get_address( xorstr_( "C_BaseViewModel::UpdateAllViewmodelAddons" ) ).as< void( __thiscall* )( void* ) >( );
		
		return function( this );

	}

	auto remove_viewmodel_arm_models( ) {

		static auto function = m_modules.m_client_dll.get_address( xorstr_( "C_BaseViewModel::RemoveViewmodelArmModels" ) ).as< void( __thiscall* )( void* ) >( );
		
		return function( this );

	}

	auto remove_viewmodel_label( ) {

		static auto function = m_modules.m_client_dll.get_address( xorstr_( "C_BaseViewModel::RemoveViewmodelLabel" ) ).as< void( __thiscall* )( void* ) >( );
		
		return function( this );

	}

	auto remove_viewmodel_stat_track( ) {

		static auto function = m_modules.m_client_dll.get_address( xorstr_( "C_BaseViewModel::RemoveViewmodelStatTrak" ) ).as< void( __thiscall* )( void* ) >( );
		
		return function( this );

	}

	auto remove_viewmodel_stickers( ) {

		static auto function = m_modules.m_client_dll.get_address( xorstr_( "C_BaseViewModel::RemoveViewmodelStickers" ) ).as< void( __thiscall* )( void* ) >( );
		
		return function( this );

	}

};
