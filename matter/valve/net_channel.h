#pragma once

struct net_channel {

	auto send_net_msg( void* msg, const bool force_reliable = false, const bool voice = false ) {

		return m_utils.get_v_func< bool( __thiscall* )( void*, void*, bool, bool ) >( this, 40 )( this, msg, force_reliable, voice );

	}

};
