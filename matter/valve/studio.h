#pragma once

#include "signatures/signatures.h"

struct mstudioseqdesc {

	char _pad0[ 0xc4 ]; 
	int numanimtags; 

};

struct studio_hdr {

	auto seqdesc( const int seq ) {

		const auto function = m_signatures.m_seqdesc.as< mstudioseqdesc& ( __thiscall* )( void*, int ) >( );

		return function( this, seq );

	}

};