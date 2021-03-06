#include "render.h"

bool render::setup( ) {

	create_font( m_fonts.verdana, xorstr_( "verdana" ), 12, 500, fontflag_antialias );
		
	create_font( m_fonts.smallest_pixel_7, xorstr_( "smallest pixel-7" ), 11, 500, fontflag_outline );

	create_font( m_fonts.matter_icons, xorstr_( "matter-icons" ), 18, 500, fontflag_antialias );

	m_interfaces.m_surface->get_screen_size( m_screen.w, m_screen.h );

	return true;

}

void render::draw_line( int x0, int y0, int x1, int y1, const color& color ) {

	m_interfaces.m_surface->draw_set_color( color.r, color.g, color.b, color.a );

	m_interfaces.m_surface->draw_line( x0, y0, x1, y1 );

}

void render::draw_filled_rect( int x, int y, int width, int height, const color& color, int flags ) {

	m_interfaces.m_surface->draw_set_color( color.r, color.g, color.b, color.a );

	handle_flags( x, y, width, height, flags );

	m_interfaces.m_surface->draw_filled_rect( x, y, x + width, y + height );

}

void render::draw_outlined_rect( int x, int y, int width, int height, const color& color, int flags ) {

	m_interfaces.m_surface->draw_set_color( color.r, color.g, color.b, color.a );

	handle_flags( x, y, width, height, flags );

	m_interfaces.m_surface->draw_outlined_rect( x, y, x + width, y + height );

}

void render::draw_gradient( int x, int y, int width, int height, color color1, const color color2, bool horizontal ) {

	m_interfaces.m_surface->draw_set_color( color1.r, color1.g, color1.b, color1.a );
	m_interfaces.m_surface->draw_filled_rect_fade( x, y, x + width, y + height, 255, 255, horizontal );

	m_interfaces.m_surface->draw_set_color( color2.r, color2.g, color2.b, color2.a ); 
	m_interfaces.m_surface->draw_filled_rect_fade( x, y, x + width, y + height, 0, 255, horizontal );

}

void render::draw_text( h_font& font, int x, int y, std::wstring_view text, const color& color, int flags ) {

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

void render::draw_text( h_font& font, int x, int y, std::string_view text, const color& color, int flags ) {

	draw_text( font, x, y, std::wstring( text.begin( ), text.end( ) ), color, flags );

}

dimension render::get_text_size( h_font font, std::wstring_view text ) {

	dimension text_area;
	m_interfaces.m_surface->get_text_size( font, text.data( ), text_area.m_width, text_area.m_height );

	return text_area;

}


std::string_view render::format_text( std::string_view format, ... ) {

	if ( std::strlen( format.data( ) ) >= sizeof( m_buffer ) )
		return std::string_view( );

	va_list arguments;

	va_start( arguments, format );

	std::memset( m_buffer, '\0', sizeof( m_buffer ) );
	vsprintf_s( m_buffer, format.data( ), arguments );

	std::string_view text = m_buffer;

	va_end( arguments );

	return text;

}

void render::create_font( h_font& font, std::string_view name, int tall, int weight, int flags ) {

	font = m_interfaces.m_surface->create_font( );
		
	m_interfaces.m_surface->set_font_glyph( font, name.data( ), tall, weight, 0, 0, flags );

}

void render::handle_flags( int& x, int& y, int width, int height, int flags ) {

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
