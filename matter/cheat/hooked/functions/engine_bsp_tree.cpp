#include "../hooked.h"

#include <intrin.h>

int __fastcall hooked::engine_bsp_tree_fn::list_leaves_in_box( void* ecx, void* edx, vector_3d& min, vector_3d& max, unsigned short* list, int list_max ) {

	static auto o_list_leaves_in_box = m_modules.m_engine_dll.get< decltype( &list_leaves_in_box ) >( xorstr_( "CEngineBSPTree::ListLeavesInBox" ) );

	static std::uintptr_t insert_into_tree_call_list_leaves_in_box = m_modules.m_client_dll.get_address( xorstr_( "CClientLeafSystem::InsertIntoTree" ) ).add( 0x5 ).as< std::uintptr_t >( );
	
	if ( reinterpret_cast< std::uintptr_t >( _ReturnAddress( ) ) != insert_into_tree_call_list_leaves_in_box )
		return o_list_leaves_in_box( ecx, edx, min, max, list, list_max );

	rendable_info* info = *reinterpret_cast< rendable_info** >( reinterpret_cast< std::uintptr_t >( _AddressOfReturnAddress( ) ) + 0x14 );

	if ( !info || !info->m_renderable )
		return o_list_leaves_in_box( ecx, edx, min, max, list, list_max );

	// todo: checks on what entity is xqz enabled
	
	base_entity* entity = info->m_renderable->get_client_unknown( )->get_base_entity( );

	if ( !entity || !entity->is_player( ) )
		return o_list_leaves_in_box( ecx, edx, min, max, list, list_max );

	info->m_flags &= ~0x100;
	info->m_render_in_fast_reflection |= 0x40;

	constexpr float max_coord_flat = 16384.f;
	constexpr float min_coord_flat = -16384.f;

	static vector_3d map_min = vector_3d( min_coord_flat, min_coord_flat, min_coord_flat );
	static vector_3d map_max = vector_3d( max_coord_flat, max_coord_flat, max_coord_flat );

	return o_list_leaves_in_box( ecx, edx, map_min, map_max, list, list_max );
	
}
