#include "misc.h"

#include "../../cheat.h"

// fucking aimwhere paste

void misc::movement_fix( q_angle& angle ) {

	if ( !m_globals.m_local_player.pointer->is_alive( ) )
		return;

	vector_3d view_forward, view_right, view_up, cmd_forward, cmd_right, cmd_up;
	
	q_angle view_angles = m_globals.m_cmd->m_view_angles;
	view_angles.normalize( );
	
	m_mathlib_base.angle_vectors( angle, &view_forward, &view_right, &view_up );
	m_mathlib_base.angle_vectors( view_angles, &cmd_forward, &cmd_right, &cmd_up );

	float v8 = sqrtf( ( view_forward.x * view_forward.x ) + ( view_forward.y * view_forward.y ) );
	float v10 = sqrtf( ( view_right.x * view_right.x ) + ( view_right.y * view_right.y ) );
	float v12 = sqrtf( view_up.z * view_up.z );
	
	vector_3d normal_view_forward( ( 1.f / v8 ) * view_forward.x, ( 1.f / v8 ) * view_forward.y, 0.f );
	vector_3d normal_view_right( ( 1.f / v10 ) * view_right.x, ( 1.f / v10) * view_right.y, 0.f );
	vector_3d normal_view_up( 0.f, 0.f, ( 1.f / v12 ) * view_up.z );

	float v14 = sqrtf( ( cmd_forward.x * cmd_forward.x ) + ( cmd_forward.y * cmd_forward.y ) );
	float v16 = sqrtf( ( cmd_right.x * cmd_right.x ) + ( cmd_right.y * cmd_right.y ) );
	float v18 = sqrtf( cmd_up.z * cmd_up.z );

	vector_3d normal_cmd_fwd( ( 1.f / v14 ) * cmd_forward.x, ( 1.f / v14 ) * cmd_forward.y, 0.f );
	vector_3d normal_cmd_right( ( 1.f / v16 ) * cmd_right.x, ( 1.f / v16 ) * cmd_right.y, 0.f );
	vector_3d normal_cmd_up( 0.f, 0.f, ( 1.f / v18 ) * cmd_up.z );

	float v22 = normal_view_forward.x * m_globals.m_cmd->m_forward_move;
	float v26 = normal_view_forward.y * m_globals.m_cmd->m_forward_move;
	float v28 = normal_view_forward.z * m_globals.m_cmd->m_forward_move;
	
	float v24 = normal_view_right.x * m_globals.m_cmd->m_side_move;
	float v23 = normal_view_right.y * m_globals.m_cmd->m_side_move;
	float v25 = normal_view_right.z * m_globals.m_cmd->m_side_move;
	
	float v30 = normal_view_up.x * m_globals.m_cmd->m_up_move;
	float v27 = normal_view_up.z * m_globals.m_cmd->m_up_move;
	float v29 = normal_view_up.y * m_globals.m_cmd->m_up_move;

	m_globals.m_cmd->m_forward_move = ( ( ( ( normal_cmd_fwd.x * v24 ) + ( normal_cmd_fwd.y * v23 ) ) + ( normal_cmd_fwd.z * v25 ) )
		+ ( ( ( normal_cmd_fwd.x * v22 ) + ( normal_cmd_fwd.y * v26 ) ) + ( normal_cmd_fwd.z * v28 ) ) )
		+ ( ( ( normal_cmd_fwd.y * v30 ) + ( normal_cmd_fwd.x * v29 ) ) + ( normal_cmd_fwd.z * v27 ) );
	
	m_globals.m_cmd->m_side_move = ( ( ( ( normal_cmd_right.x * v24 ) + ( normal_cmd_right.y * v23 ) ) + ( normal_cmd_right.z * v25 ) )
		+ ( ( ( normal_cmd_right.x * v22 ) + ( normal_cmd_right.y * v26 ) ) + ( normal_cmd_right.z * v28 ) ) )
		+ ( ( ( normal_cmd_right.x * v29 ) + ( normal_cmd_right.y * v30 ) ) + ( normal_cmd_right.z * v27 ) );
	
	m_globals.m_cmd->m_up_move = ( ( ( ( normal_cmd_up.x * v23 ) + ( normal_cmd_up.y * v24 ) ) + ( normal_cmd_up.z * v25 ) )
		+ ( ( ( normal_cmd_up.x * v26 ) + ( normal_cmd_up.y * v22 ) ) + ( normal_cmd_up.z * v28 ) ) )
		+ ( ( ( normal_cmd_up.x * v30 ) + ( normal_cmd_up.y * v29 ) ) + ( normal_cmd_up.z * v27 ) );

	m_globals.m_cmd->m_forward_move = std::clamp( m_globals.m_cmd->m_forward_move, -450.f, 450.f );
	m_globals.m_cmd->m_side_move = std::clamp( m_globals.m_cmd->m_side_move, -450.f, 450.f );
	m_globals.m_cmd->m_up_move = std::clamp( m_globals.m_cmd->m_up_move, -320.f, 320.f );

	m_globals.m_cmd->m_buttons &= ~( in_forward | in_back | in_move_right | in_move_left );

}
