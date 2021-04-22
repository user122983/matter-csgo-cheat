#pragma once

#include "../modules/modules.h"

struct mstudioseqdesc {

	char _pad0[ 0xc4 ]; 
	int numanimtags; 

};

struct studio_hdr {

	auto seqdesc( int seq ) {

		static auto function = m_modules.m_client_dll.get_address( "CStudioHdr::pSeqdesc" ).as< mstudioseqdesc& ( __thiscall* )( void*, int ) >( );
		
		return function( this, seq );

	}

};