#include "../hooked.h"

struct cl_msg_move {

	cl_msg_move( ) {

		m_net_message_vtable = m_modules.m_engine_dll.get_address( xorstr_( "CL_SendMove" ) ).add( 0x76 ).to< std::size_t >( );
		m_cl_msg_move_vtable = m_modules.m_engine_dll.get_address( xorstr_( "CL_SendMove" ) ).add( 0x82 ).to< std::size_t >( );
		m_allocated_memory = m_modules.m_engine_dll.get_address( xorstr_( "CL_SendMove" ) ).add( 0x7b ).to< void* >( );

		m_unknown = 15;

		m_flags = 3;

		m_unknown1 = 0;
		m_unknown2 = 0;
		m_unknown3 = 0;
		m_unknown4 = 0;
		m_unknown5 = 0;

	}

	~cl_msg_move( ) {

		static auto function = m_modules.m_engine_dll.get_address( xorstr_( "CCLCMsg_Move::Deconstuctor" ) ).as< void( __thiscall* )( void* ) >( );

		function( this );

	}

	auto set_num_backup_commands( int backup_commands ) {

		m_backup_commands = backup_commands;

	}

	auto set_num_new_commands( int new_commands ) {

		m_new_commands = new_commands;

	}

	auto set_data( unsigned char* data, int num_bytes_written ) {

		m_flags |= 4;

		if ( m_allocated_memory == m_modules.m_engine_dll.get_address( xorstr_( "CL_SendMove" ) ).add( 0x7b ).to< void* >( ) ) {

			address new_memory = address( m_interfaces.m_mem_alloc->alloc( 24 ) );
			if ( new_memory ) {

				new_memory.add( 0x14 ).set( 15 );
				new_memory.add( 0x10 ).set( 0 );
				new_memory.set< unsigned char >( 0 );

			}

			m_allocated_memory = new_memory;

		}

		static auto function = m_modules.m_engine_dll.get_address( xorstr_( "CCLCMsg_Move::set_data" ) ).as< void* ( __thiscall* )( void*, unsigned char*, std::size_t ) >( );

		return function( m_allocated_memory, data, num_bytes_written );

	}

	int m_net_message_vtable;
	int m_cl_msg_move_vtable; 
	int m_unknown1; 
	int m_backup_commands; 
	int m_new_commands; 
	void* m_allocated_memory; 
	int m_unknown2; 
	int m_flags; 
	char m_unknown3; 
	char _pad0[ 0x3 ]; 
	char m_unknown4; 
	char _pad1[ 0xf ];
	int m_unknown5; 
	int m_unknown; 
	bf_write m_data_out; 

};

void __cdecl hooked::cl_main_fn::cl_send_move( ) {

	int next_command_nr = m_interfaces.m_client_state->m_lastoutgoingcommand + m_interfaces.m_client_state->m_choked_commands + 1;
	int choked_commands = m_interfaces.m_client_state->m_choked_commands;

	byte data[ 4000 ];
	cl_msg_move move_msg;

	move_msg.m_data_out.start_writing( data, sizeof( data ) );

	int cl_cmdbackup = 2;
	int backup_commands = std::clamp( cl_cmdbackup, 0, 7 );
	
	int new_commands = std::clamp( choked_commands + 1, 0, 17 );

	move_msg.set_num_backup_commands( backup_commands );
	move_msg.set_num_new_commands( new_commands );

	//int extra_command = choked_commands + 1 - new_commands;
	
	int num_cmds = new_commands + backup_commands;
	int from = -1;
	bool ok = true;

	for ( int to = next_command_nr - num_cmds + 1; to <= next_command_nr; ++to ) {

		bool is_new_cmd = to >= ( next_command_nr - new_commands + 1 );

		ok = ok && m_interfaces.m_client->write_usercmd_delta_to_buffer( 0, &move_msg.m_data_out, from, to, is_new_cmd );
		from = to;

	}

	if ( ok ) {

/*		if ( extra_command )
			m_interfaces.m_client_state->m_net_channel->m_choked_packets -= extra_command;*/
		
		move_msg.set_data( move_msg.m_data_out.get_data( ), move_msg.m_data_out.get_num_bytes_written( ) );

		m_interfaces.m_client_state->m_net_channel->send_net_msg( &move_msg );

	}

}

void __cdecl hooked::cl_main_fn::cl_move( void* ecx, void* edx, float accumulated_extra_samples, bool final_tick ) {

	static auto o_cl_move = m_modules.m_engine_dll.get< decltype( &cl_move ) >( xorstr_( "CL_Move" ) );

	o_cl_move( ecx, edx, accumulated_extra_samples, final_tick );
	
}