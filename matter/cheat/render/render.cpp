#include "render.h"

bool render::setup( ) {

	create_font( m_fonts.verdana, "verdana", 12, 500, fontflag_dropshadow );

	create_font( m_fonts.smallest_pixel_7, "smallest pixel-7", 11, 500, fontflag_outline );

	create_font( m_fonts.matter_icons, "cheat-icons", 18, 500, fontflag_antialias );

	m_interfaces.m_surface->get_screen_size( m_screen.w, m_screen.h );

	return true;

}

void render::draw_line( const int x0, const int y0, const int x1, const int y1, const color& color ) {

	m_interfaces.m_surface->draw_set_color( color.r, color.g, color.b, color.a );

	m_interfaces.m_surface->draw_line( x0, y0, x1, y1 );

}

void render::draw_filled_rect( int x, int y, const int width, const int height, const color& color, const int flags ) {

	m_interfaces.m_surface->draw_set_color( color.r, color.g, color.b, color.a );

	handle_flags( x, y, width, height, flags );

	m_interfaces.m_surface->draw_filled_rect( x, y, x + width, y + height );

}

void render::draw_outlined_rect( int x, int y, const int width, const int height, const color& color, const int flags ) {

	m_interfaces.m_surface->draw_set_color( color.r, color.g, color.b, color.a );

	handle_flags( x, y, width, height, flags );

	m_interfaces.m_surface->draw_outlined_rect( x, y, x + width, y + height );

}

void render::draw_gradient( const int x, const int y, const int width, const int height, const color color1, const color color2, const bool horizontal ) {

	m_interfaces.m_surface->draw_set_color( color1.r, color1.g, color1.b, color1.a );
	m_interfaces.m_surface->draw_filled_rect_fade( x, y, x + width, y + height, 255, 255, horizontal );

	m_interfaces.m_surface->draw_set_color( color2.r, color2.g, color2.b, color2.a ); 
	m_interfaces.m_surface->draw_filled_rect_fade( x, y, x + width, y + height, 0, 255, horizontal );

}

void render::draw_text( const h_font& font, int x, int y, const std::wstring_view text, const color& color, const int flags ) {

	if ( flags ) {
		
		int width, height;
		m_interfaces.m_surface->get_text_size( font, text.data( ), width, height );

		handle_flags( x, y, width, height, flags );
		
	}

	m_interfaces.m_surface->draw_set_text_color( color.r, color.g, color.b, color.a );
	m_interfaces.m_surface->draw_set_text_font( font );
	m_interfaces.m_surface->draw_set_text_pos( x, y );
	m_interfaces.m_surface->draw_print_text( text.data( ), text.size( ) );

}

void render::draw_text( const h_font& font, const int x, const int y, const std::string_view text, const color& color, const int flags ) const {

	draw_text( font, x, y, std::wstring( text.begin( ), text.end( ) ), color, flags );

}

std::string_view render::format_text( std::string_view format, ... ) {

	if ( std::strlen( format.data( ) ) >= sizeof( m_buffer ) )
		return std::string_view( );

	va_list arguments;

	va_start( arguments, format );

	std::memset( m_buffer, '\0', sizeof( m_buffer ) );
	vsprintf_s( m_buffer, format.data( ), arguments );

	const auto text = m_buffer;

	va_end( arguments );

	return text;

}

dimension render::get_text_size( const h_font font, const std::wstring_view text ) {
	
	dimension text_area = { };
	m_interfaces.m_surface->get_text_size( font, text.data( ), text_area.m_width, text_area.m_height );

	return text_area;
	
}

void render::create_font( h_font& font, const std::string_view name, const int tall, const int weight, const int flags ) {

	font = m_interfaces.m_surface->create_font( );
		
	m_interfaces.m_surface->set_font_glyph( font, name.data( ), tall, weight, 0, 0, flags );

}

void render::handle_flags( int& x, int& y, const int width, const int height, const int flags ) {

	if ( !flags )
		return;

	if ( flags & x_right )
		x -= width;
	else if ( flags & x_centre )
		x -= width / 2;

	if ( flags & y_bottom )
		y -= height;
	else if ( flags & y_centre )
		y -= height / 2;

}
