#pragma once

#include "../cheat.h"
#include "../menu/gui/definitions.h"

#include "../../other/color/color.h"

enum render_flags {

	x_right = 1,
	x_centre = 1 << 1,
	
	y_bottom = 1 << 2,
	y_centre = 1 << 3,

};

struct render {

	bool setup( );

	static void draw_line( int x0, int y0, int x1, int y1, const color& color );

	static void draw_filled_rect( int x, int y, int width, int height, const color& color, int flags = { } );

	static void draw_outlined_rect( int x, int y, int width, int height, const color& color, int flags = { } );

	static void draw_gradient( int x, int y, int width, int height, color color1, color color2, bool horizontal );

	static void draw_text( const h_font& font, int x, int y, std::wstring_view text, const color& color, int flags = { } );

	void draw_text( const h_font& font, int x, int y, std::string_view text, const color& color, int flags = { } ) const;

	std::string_view format_text( std::string_view format, ... );

	static dimension get_text_size( h_font font, std::wstring_view text );
	
	struct {

		h_font verdana;

		h_font smallest_pixel_7;

		h_font matter_icons;

		
	} m_fonts = { };

	struct {

		int w, h;

	} m_screen = { };

private:

	static void create_font( h_font& font, std::string_view name, int tall, int weight, int flags = { } );

	static void handle_flags( int& x, int& y, int width, int height, int flags );

	char m_buffer[ 256 ] = { };

};

inline render m_render;
