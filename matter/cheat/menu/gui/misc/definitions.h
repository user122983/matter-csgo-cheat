#pragma once

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

    "/", "m1", "m2", "", "m3", "m4", "m5", "",
    "bspace", "tab", "", "", "", "enter", "", "", "shift", "ctrl", "alt",
    "pause", "capslock", "", "", "", "", "", "", "esc", "", "", "", "",
    "space", "pup", "pdown", "end", "home", "left", "up", "right",
    "down", "", "", "", "", "ins", "del", "", "0", "1", "2", "3",
    "4", "5", "6", "7", "8", "9", "", "", "", "", "", "", "", "a",
    "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n",
    "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "lwin",
    "rwin", "", "", "", "num0", "num1", "num2", "num3", "num4", "num5",
    "num6", "num7", "num8", "num9", "*", "+", "_", "-", ".", "/", "f1",
    "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10", "f11", "f12",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "scroll", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "lshift", "rshift", "lctrl", "rctrl", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", " );", "+", ",", "-", ".", "/?", "~", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
    "", "", "", "", "{", "\\", "}", "/"

};