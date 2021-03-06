#include "../hooked.h"

void __fastcall hooked::studio_render_fn::draw_model( studio_render_context* ecx, void* edx, void* results, draw_model_info& info, void* bone_to_world, float* flex_weights, float* flex_delayed_rates, vector_3d& origin, int flags ) {

	static auto o_draw_model = m_modules.m_studiorender_dll.get< decltype( &draw_model ) >( xorstr_( "CStudioRenderContext::DrawModel" ) );

	if ( !m_globals.m_local_player.pointer || !info.m_client_entity )
		return o_draw_model( ecx, edx, results, info, bone_to_world, flex_weights, flex_delayed_rates, origin, flags );

	base_entity* entity = reinterpret_cast< base_entity* >( info.m_client_entity - 0x4 ); 
	if ( entity && entity->is_player( ) && entity->get_team( ) != m_globals.m_local_player.pointer->get_team() ) {

		ecx->set_color( color( 37, 37, 37 ) );
		
		static material* material = m_interfaces.m_material_system->find_material( xorstr_( "debug/debugambientcube" ), xorstr_( "Model textures" ) );
		ecx->set_material( material );

		o_draw_model( ecx, edx, results, info, bone_to_world, flex_weights, flex_delayed_rates, origin, flags );

		ecx->set_color( color( 200, 123, 150 ) );

		ecx->set_material( material, false );

		o_draw_model( ecx, edx, results, info, bone_to_world, flex_weights, flex_delayed_rates, origin, flags );

		ecx->set_material( nullptr );

		return;

	}

	return o_draw_model( ecx, edx, results, info, bone_to_world, flex_weights, flex_delayed_rates, origin, flags );

}
