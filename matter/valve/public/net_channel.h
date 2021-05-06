#pragma once

struct net_channel {

	auto send_net_msg( void* msg, bool force_reliable = false, bool voice = false ) {

		return m_memory.get_v_func< bool( __thiscall* )( void*, void*, bool, bool ) >( this, 40 )( this, msg, force_reliable, voice );

	}
	
	char _pad0[ 0x14 ];
	bool m_processing_messages;
	bool m_should_delete;
	bool m_stop_processing;
	char _pad1[ 0x1 ];
	int	m_out_sequence;
	int	m_in_sequence;
	int	m_out_sequence_ack;
	int	m_out_reliable_state;
	int	m_in_reliable_state;
	int	m_choked_packets;
	char _pad2[ 0x414 ];

};
