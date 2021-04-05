#pragma once

struct color {

	color( ) : r{ 0 }, g{ 0 }, b{ 0 }, a{ 255 } { };

	color( const int r, const int g, const int b, const int a = 255 ) : r{ r }, g{ g }, b{ b }, a{ a } { };

	int r, g, b, a;

};