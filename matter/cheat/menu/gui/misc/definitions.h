#pragma once

#include "../../../../other/xorstr/xorstr.h"

#include <string_view>

struct area {

	int m_x;
	int m_y;
	int m_width;
	int m_height;

};

struct dimension {

	int m_width;
	int m_height;

};

struct point {

	int m_x;
	int m_y;

};

enum widget_type  {

    widget_type_box,
	widget_type_checkbox,
	widget_type_container,
	widget_type_key_binder,
	widget_type_slider,
	widget_type_tab_panel,
	widget_type_color_picker

};

inline std::string_view m_virtual_key_codes[ 223 ] = {
	
    xorstr_( "/" ), xorstr_( "m1" ), xorstr_( "m2" ), xorstr_( "" ), xorstr_( "m3" ), xorstr_( "m4" ), xorstr_( "m5" ), xorstr_( "" ),
    xorstr_( "bspace" ), xorstr_( "tab" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "enter" ), xorstr_( "" ), xorstr_( "" ),
	xorstr_( "shift" ), xorstr_( "ctrl" ), xorstr_( "alt" ), xorstr_( "pause" ), xorstr_( "capslock" ), xorstr_( "" ), xorstr_( "" ),
	xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "esc" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ),
    xorstr_( "space" ), xorstr_( "pup" ), xorstr_( "pdown" ), xorstr_( "end" ), xorstr_( "home" ), xorstr_( "left" ), xorstr_( "up" ),
	xorstr_( "right" ), xorstr_( "down" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "ins" ), xorstr_( "del" ),
	xorstr_( "" ), xorstr_( "0" ), xorstr_( "1" ), xorstr_( "2" ), xorstr_( "3" ), xorstr_( "4" ), xorstr_( "5" ), xorstr_( "6" ), xorstr_( "7" ),
    xorstr_( "8" ), xorstr_( "9" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ),
	xorstr_( "a" ), xorstr_( "b" ), xorstr_( "c" ), xorstr_( "d" ), xorstr_( "e" ), xorstr_( "f" ), xorstr_( "g" ), xorstr_( "h" ), xorstr_( "i" ),
	xorstr_( "j" ), xorstr_( "k" ), xorstr_( "l" ), xorstr_( "m" ), xorstr_( "n" ), xorstr_( "o" ), xorstr_( "p" ), xorstr_( "q" ), xorstr_( "r" ),
	xorstr_( "s" ), xorstr_( "t" ), xorstr_( "u" ), xorstr_( "v" ), xorstr_( "w" ), xorstr_("x" ), xorstr_( "y" ), xorstr_( "z" ), xorstr_( "lwin" ),
    xorstr_( "rwin" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "num0" ), xorstr_( "num1" ), xorstr_( "num2" ), xorstr_( "num3" ),
	xorstr_( "num4" ), xorstr_( "num5" ), xorstr_( "num6" ), xorstr_( "num7" ), xorstr_( "num8" ), xorstr_( "num9" ), xorstr_( "*" ), xorstr_( "+" ),
	xorstr_( "_" ), xorstr_( "-" ), xorstr_( "." ), xorstr_( "/" ), xorstr_( "f1" ), xorstr_( "f2" ), xorstr_( "f3" ), xorstr_( "f4" ), xorstr_( "f5" ),
	xorstr_( "f6" ), xorstr_( "f7" ), xorstr_( "f8" ), xorstr_( "f9" ), xorstr_( "f10" ), xorstr_( "f11" ), xorstr_( "f12" ), xorstr_( "" ),
	xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ),
	xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ),
	xorstr_( "scroll" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ),
	xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "lshift" ), xorstr_( "rshift" ), xorstr_( "lctrl" ), xorstr_( "rctrl" ),
	xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ),
	xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ),
	xorstr_( "" ), xorstr_( "" ), xorstr_( " );" ), xorstr_( "+" ), xorstr_( "," ), xorstr_( "-" ), xorstr_( "." ), xorstr_( "/?" ), xorstr_( "~" ), xorstr_( "" ),
	xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ),
	xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ),
	xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "" ), xorstr_( "{" ), xorstr_( "\\" ), xorstr_( "}" ), xorstr_( "/" )
	
};
