#include <stdio.h>
#include "headers/internal.hpp"

Color rgb(BYTE red, BYTE green, BYTE blue) {
	if (red > 5) red = 0;
	if (green > 5) green = 0;
	if (blue > 5) blue = 0;
	return static_cast<Color>(red * 36 + green * 6 + blue + 16);
}

Color grayscale(BYTE intensity) {
	if (intensity > 23) intensity = 0;
	return static_cast<Color>(232+intensity);
}

//internals

//Legacy, will be rewritten later
void invertColors() {
	//Value swap
	virt.background = static_cast<Color>(virt.foreground + virt.background);
	virt.foreground = static_cast<Color>(virt.background - virt.foreground);
	virt.background = static_cast<Color>(virt.background - virt.foreground);

	//set new colors
	printf("\x1B[38;5;%dm\x1B[48;5;%dm", virt.foreground, virt.background); 
}