#pragma once

#include "clockdriftmgr.h"

struct net_channel;

struct client_state {

	char _pad0[ 0x9c ];
	net_channel* m_net_channel;	
	char _pad2[ 0x88 ];
	clockdriftmgr m_clockdriftmgr;	
	char _pad1[ 0x4BB8 ];	
	int m_lastoutgoingcommand;
	int m_choked_commands;

};
