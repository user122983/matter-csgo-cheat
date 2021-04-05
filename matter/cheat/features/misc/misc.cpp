#include "misc.h"

#include "../globals.h"
#include "../../cheat.h"

#include <algorithm>

void misc::movement_fix( q_angle& angle ) const {

	if ( !m_globals.m_local_player->is_alive( ) )
		return;

	vector_3d view_forward, view_right, view_up, cmd_forward, cmd_right, cmd_up;
	auto view_angles = m_globals.m_cmd->m_view_angles;
	view_angles.normalize( );
	
	m_mathlib_base.angle_vectors( angle, &view_forward, &view_right, &view_up );
	m_mathlib_base.angle_vectors( view_angles, &cmd_forward, &cmd_right, &cmd_up );

	const auto v8 = sqrtf( ( view_forward.x * view_forward.x ) + ( view_forward.y * view_forward.y ) );
	const auto v10 = sqrtf( ( view_right.x * view_right.x ) + ( view_right.y * view_right.y ) );
	const auto v12 = sqrtf( view_up.z * view_up.z );
	 
	const vector_3d normal_view_forward( ( 1.f / v8 ) * view_forward.x, ( 1.f / v8 ) * view_forward.y, 0.f );
	const vector_3d normal_view_right( ( 1.f / v10 ) * view_right.x, ( 1.f / v10) * view_right.y, 0.f );
	const vector_3d normal_view_up( 0.f, 0.f, ( 1.f / v12 ) * view_up.z );

	const auto v14 = sqrtf( ( cmd_forward.x * cmd_forward.x ) + ( cmd_forward.y * cmd_forward.y ) );
	const auto v16 = sqrtf( ( cmd_right.x * cmd_right.x ) + ( cmd_right.y * cmd_right.y ) );
	const auto v18 = sqrtf( cmd_up.z * cmd_up.z );

	const vector_3d normal_cmd_fwd( ( 1.f / v14) * cmd_forward.x, ( 1.f / v14 ) * cmd_forward.y, 0.f );
	const vector_3d norm_cmd_right( ( 1.f / v16) * cmd_right.x, ( 1.f / v16 ) * cmd_right.y, 0.f );
	const vector_3d norm_cmd_up( 0.f, 0.f, ( 1.f / v18 ) * cmd_up.z );

	const auto v22 = normal_view_forward.x * m_globals.m_cmd->m_forward_move;
	const auto v26 = normal_view_forward.y * m_globals.m_cmd->m_forward_move;
	const auto v28 = normal_view_forward.z * m_globals.m_cmd->m_forward_move;
	const auto v24 = normal_view_right.x * m_globals.m_cmd->m_side_move;
	const auto v23 = normal_view_right.y * m_globals.m_cmd->m_side_move;
	const auto v25 = normal_view_right.z * m_globals.m_cmd->m_side_move;
	const auto v30 = normal_view_up.x * m_globals.m_cmd->m_up_move;
	const auto v27 = normal_view_up.z * m_globals.m_cmd->m_up_move;
	const auto v29 = normal_view_up.y * m_globals.m_cmd->m_up_move;

	m_globals.m_cmd->m_forward_move = ( ( ( ( normal_cmd_fwd.x * v24 ) + ( normal_cmd_fwd.y * v23 ) ) + ( normal_cmd_fwd.z * v25 ) )
		+ ( ( ( normal_cmd_fwd.x * v22) + ( normal_cmd_fwd.y * v26 ) ) + ( normal_cmd_fwd.z * v28 ) ) )
		+ ( ( ( normal_cmd_fwd.y * v30) + ( normal_cmd_fwd.x * v29 ) ) + ( normal_cmd_fwd.z * v27 ) );
	
	m_globals.m_cmd->m_side_move = ( ( ( ( norm_cmd_right.x * v24 ) + ( norm_cmd_right.y * v23 ) ) + ( norm_cmd_right.z * v25 ) )
		+ ( ( ( norm_cmd_right.x * v22 ) + ( norm_cmd_right.y * v26 ) ) + ( norm_cmd_right.z * v28 ) ) )
		+ ( ( ( norm_cmd_right.x * v29 ) + ( norm_cmd_right.y * v30 ) ) + ( norm_cmd_right.z * v27 ) );
	
	m_globals.m_cmd->m_up_move = ( ( ( ( norm_cmd_up.x * v23 ) + ( norm_cmd_up.y * v24 ) ) + ( norm_cmd_up.z * v25 ) )
		+ ( ( ( norm_cmd_up.x * v26) + ( norm_cmd_up.y * v22 ) ) + ( norm_cmd_up.z * v28 ) ) )
		+ ( ( ( norm_cmd_up.x * v30) + ( norm_cmd_up.y * v29 ) ) + ( norm_cmd_up.z * v27 ) );

	m_globals.m_cmd->m_forward_move = std::clamp( m_globals.m_cmd->m_forward_move, -450.f, 450.f );
	m_globals.m_cmd->m_side_move = std::clamp( m_globals.m_cmd->m_side_move, -450.f, 450.f );
	m_globals.m_cmd->m_up_move = std::clamp( m_globals.m_cmd->m_up_move, -320.f, 320.f );
	
}