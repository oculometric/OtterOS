/* Copyright (C) 2018 JavaxCosten - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the LICENSE, found in the top level directory.
*/

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "include/utils.cc"
#include "include/globals.cc"
#include "include/terminal.cc"
#include "include/kbdus.h"
#include "include/graphicKernel.cc"

#define PIC1 0x20
#define PIC2 0xA0

#define ICW1 0x11
#define ICW4 0x01

void init_pics(int pic1, int pic2)
{
	/* send ICW1 */
	outb(PIC1, ICW1);
	outb(PIC2, ICW1);

	/* send ICW2 */
	outb(PIC1 + 1, pic1);
	outb(PIC2 + 1, pic2);

	/* send ICW3 */
	outb(PIC1 + 1, 4);
	outb(PIC2 + 1, 2);

	/* send ICW4 */
	outb(PIC1 + 1, ICW4);
	outb(PIC2 + 1, ICW4);

	/* disable all IRQs */
	outb(PIC1 + 1, 0xFF);
}

bool isWaitingForUp = false;

bool leftShiftDown = false;
bool rightShiftDown = false;

void terminalKernel () {
	tInitialize();
	println("Well... this is OtterOS so far!");
	println("Warning! This OS melts PHP programmers.");
	println("");
	tFillLineWithChar ('█');
	print("cosh -> ");
	char c = 0;
	init_pics(0x20, 0x28);
	do {
		if (inb(0x60) != c) {
			c = inb (0x60);
			if (c > 0) {
				int a = c;
				char ch = ' ';
				if (a == 0x2A) {
					leftShiftDown = !leftShiftDown;
				} else if (a == 0x36) {
					rightShiftDown = !rightShiftDown;
				} else {
					ch = normalmap[a];
					if (rightShiftDown || leftShiftDown) {
						ch = shiftmap[a];
					}
					if (ch == '\n') {
						println("");
						if (terminal_row+1 >= VGA_HEIGHT ) {
							terminal_row = 0;
							tInitialize();
						}
						executeLine();
					} else if (ch == '\b') {
						tDeleteChar();
					} else if (ch == -1) {
						if (terminal_column > 8) {
							terminal_column--;
						}
						updateCursorLocation();
					} else if (ch == -2) {
						if (terminal_column < VGA_WIDTH) {
							terminal_column++;
						}
						updateCursorLocation();
					} else if (ch == -3) {
						if (histLoc > 0) {histLoc--;updateInLineToHistory();}
					} else if (ch == -4) {
						if (histLoc < arraylen(inputHist)) {histLoc++;updateInLineToHistory();}
					} else {
						currentInLine[terminal_column - 8] = ch;
						tPutChar(ch);
					}
				}
			}
		}
	}
	while(c!=1); // 1= ESCAPE
}



extern "C" void kernel_main(void) {
	char* bootmode = getValueForKey ("bootmode");
	if (strEqual (bootmode, "graphics")) {graphicalKernel();} else {terminalKernel();}
	//setPixel();
}
