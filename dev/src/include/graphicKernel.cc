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

byte *VGA;


void initScreen () {
	byte *VGA = (byte *)0xA0000;
}

int setPixel(int x, int y, int color) {

 VGA+(320*y+x)=color; //This plots a pixel at x,y

};

void graphicalKernel () {
	// Write graphical kernel base here
	initScreen();
	setPixel (10,10, COLOR_GREEN);
}
