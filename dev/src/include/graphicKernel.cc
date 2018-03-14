/* Copyright (C) 2018 JavaxCosten - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the LICENSE, found in the top level directory.
*/

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>



// void initScreen(){
// 		ScreenBufferSize = VbeModeInfoBlock.XResolution * VbeModeInfoBlock.YResolution
// 																										* (VbeModeInfoBlock.BitsPerPixel/8);
// 		ScreenZBuffer = alloc(ScreenBufferSize);
// 		CreateThread(ScreenRefreshProc, NULL);
// }

typedef unsigned char byte;

//byte *VGA = (byte *)0xA0000;
auto *VGA = (unsigned char *)0xA0000;

void initScreen () {

}

int setPixel(int x, int y, int color) {

 VGA[320*y+x]=color; //This plots a pixel at x,y

};

/* only valid for 800x600x32bpp */
static void putPixel(unsigned char* screen, int x,int y, int color) {
	unsigned where = x*4 + y*3200;
	screen[where] = color & 255;              // BLUE
	screen[where + 1] = (color >> 8) & 255;   // GREEN
	screen[where + 2] = (color >> 16) & 255;  // RED
}

static inline void inlineSetPixel (int x, int y) {
	changeToRealMode();
	asm ("mov %ah, 0x0C \n\t"
			 "mov %al, 0x13 \n\t"
	     "int $0x10 \n\t"
	     "mov %ah, 0x0C \n\t"
	     "mov %bh, 0x00 \n\t"
	     "mov %dx, 0x05 \n\t"
	     "mov %cx, 0x05 \n\t"
	     "mov %al, 15 \n\t"
	     "int $0x10"
	);
	changeToProtectedMode();
}

static void fillRect(unsigned char *vram, int x, int y, unsigned char w, unsigned char h, int color) {
    unsigned char *where = vram;
    int i, j;

    for (i = x; i < w + x; i++) {
        for (j = y; j < h + y; j++) {
            //putpixel(vram, 64 + j, 64 + i, (r << 16) + (g << 8) + b);
            where[j*4] = (color >> 16) & 255;
            where[j*4 + 1] = (color >> 8) & 255;
            where[j*4 + 2] = color & 255;
        }
        where+=3200;
    }
}

void graphicalKernel () {
	// Write graphical kernel base here
	// INTERRUPTS ARE NOT WORKING.
	initScreen();
	//setPixel (10,10, COLOR_GREEN);
	//putPixel (VGA, 50, 50, COLOR_RED);
	//inlineSetPixel (70, 70);
	//fillRect (VGA, 100, 100, 150, 150, COLOR_WHITE);
}
