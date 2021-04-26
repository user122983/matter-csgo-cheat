#pragma once

struct cs_player;
struct ray;
struct game_trace;

struct filter {

	virtual bool should_hit_entity( cs_player* player, int contents_mask ) = 0;
	virtual int get_trace_type( ) = 0;

};

struct trace_filter : filter {

	void init( cs_player* skip, int trace_type ) {

		m_skip = skip;
		m_trace_type = trace_type;
		
	}
	
	bool should_hit_entity( cs_player* player, int contents_mask ) override {
			
		return !( player == m_skip );
		
	}

	int get_trace_type( ) override {
		
		return m_trace_type;
		
	}
	
	cs_player* m_skip;
	
	int m_trace_type;
	
};

struct engine_trace {
	
	auto trace_ray( const ray& trace_ray, unsigned int mask, trace_filter* filter, game_trace* trace ) {

		return m_memory.get_v_func< void( __thiscall* )( void*, const ray&, unsigned int, trace_filter*, game_trace* ) >( this, 5 )( this, trace_ray, mask, filter, trace );

	}
	
};