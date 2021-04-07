#pragma once

#include "../client/base_animating.h"

struct base_view_model : base_animating {

	auto update_all_viewmodel_addons( ) {

		const auto function = m_signatures.m_update_all_viewmodel_addons.as< void( __thiscall* )( void* ) >( );;

		return function( this );

	}

	auto remove_viewmodel_arm_models( ) {

		const auto function = m_signatures.m_remove_viewmodel_arm_models.as< void( __thiscall* )( void* ) >( );;

		return function( this );

	}

	auto remove_viewmodel_label( ) {

		const auto function = m_signatures.m_remove_viewmodel_label.as< void( __thiscall* )( void* ) >( );;

		return function( this );

	}

	auto remove_viewmodel_stat_track( ) {

		const auto function = m_signatures.m_remove_viewmodel_stat_track.as< void( __thiscall* )( void* ) >( );;

		return function( this );

	}

	auto remove_viewmodel_stickers( ) {

		const auto function = m_signatures.m_remove_viewmodel_stickers.as< void( __thiscall* )( void* ) >( );;

		return function( this );

	}

};