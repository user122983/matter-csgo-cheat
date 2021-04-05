#include "math.h"

#include "../../cheat/render/render.h"
#include "../../valve/interfaces/interfaces.h"

bool math::world_to_screen( const vector_3d& origin, vector_2d& screen ) {

	const auto world_to_screen = m_interfaces.m_engine->get_world_to_screen_matrix( );
	const auto width = world_to_screen[ 3 ][ 0 ] * origin.x + world_to_screen[ 3 ][ 1 ] * origin.y + world_to_screen[ 3 ][ 2 ] * origin.z + world_to_screen[ 3 ][ 3 ];

	if ( width < 0.01f )
		return false;

	const auto inverse = 1.0f / width;

	screen = { ( world_to_screen[ 0 ][ 0 ] * origin.x + world_to_screen[ 0 ][ 1 ] * origin.y + world_to_screen[ 0 ][ 2 ] * origin.z + world_to_screen[ 0 ][ 3 ] ) * inverse, 
			   ( world_to_screen[ 1 ][ 0 ] * origin.x + world_to_screen[ 1 ][ 1 ] * origin.y + world_to_screen[ 1 ][ 2 ] * origin.z + world_to_screen[ 1 ][ 3 ] ) * inverse };

	screen = { m_render.m_screen.w * 0.5f + screen.x * m_render.m_screen.w * 0.5f, m_render.m_screen.h * 0.5f - screen.y * m_render.m_screen.h * 0.5f };

	return true;

}

vector_3d math::vector_transform( const vector_3d& transform, const matrix3x4& matrix ) {

	return vector_3d(

		transform.dot_product( matrix[ 0 ] ) + matrix[ 0 ][ 3 ], 
		transform.dot_product( matrix[ 1 ] ) + matrix[ 1 ][ 3 ], 
		transform.dot_product( matrix[ 2 ] ) + matrix[ 2 ][ 3 ]

	);

}
