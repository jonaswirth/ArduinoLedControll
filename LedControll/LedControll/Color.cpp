// 
// 
// 

#include "Color.h"

Color::Color() {
	red = 0;
	green = 0;
	blue = 0;
}

Color::Color(int r, int g, int b)
{
	red = r;
	green = g;
	blue = b;
}

int Color::get_red() {
	return red;
}

int Color::get_blue() {
	return blue;
}

int Color::get_green() {
	return green;
}
