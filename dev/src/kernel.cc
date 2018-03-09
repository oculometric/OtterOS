#include <stddef.h> //we can use it: it doesnt use any platform-related api functions
#include <stdint.h> //include it to get int16_t and some integer types
#include <stdbool.h>
#include "include/terminal.cc"

/* only valid for 800x600x32bpp */
static void putpixel(unsigned char* screen, int x,int y, int color) {
    unsigned where = x*4 + y*3200;
    screen[where] = color & 255;              // BLUE
    screen[where + 1] = (color >> 8) & 255;   // GREEN
    screen[where + 2] = (color >> 16) & 255;  // RED
}

//extern void setPixel(void);

void setPixel (int x, int y) {
	int i = x;
	i=y;
	asm ("mov %ah, 0x0C");
	asm ("mov %al, 0x10");
	asm ("int $0x10");

	asm ("mov %ah, 0x0C");
	asm ("mov %bh, 0");
	asm ("mov %dx, 5");
	asm ("mov %cx, 5");
	asm ("mov %al, 0x04");
	asm ("int $0x10");
}

extern "C" void kernel_main(void) {
	tInitialize();
	println("Well... this is OtterOS so far!");
	println("Warning! This OS melts PHP programmers.");
	println("");
	char block = '0x2588';
	tPutChar (block);
	tPutChar (block);
	tPutChar (block);
	tPutChar (block);
	tPutChar (block);
	//setPixel(0,0);
}
