/* # Kernel.cc #
 *
 * ## Description ##
 * The core code for OtterOS. Every other part of the project
 * branches from this starting point.
 *
 * ## Info ##
 * Created 14/03/18
 * Format C++ source
 * Written by JavaxCosten
 *
 * ## Copyright ##
 * Copyright (C) 2018 OtterOS Project - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the LICENSE, found in the top level directory.
 */

// Include libraries and other files
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "include/memory.cc"
#include "include/utils.cc"
#include "include/globals.cc"
#include "include/terminal.cc"
#include "include/kbdus.h"
#include "include/graphicKernel.cc"
#include "include/cosh.cc"

// Define keyboard inputs
#define PIC1 0x20
#define PIC2 0xA0

#define ICW1 0x11
#define ICW4 0x01

// Set up the keyboard
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


// Terminal based kernel
void terminalKernel () {
	// Set up the terminal environment
	tInitialize();

   // Prompt the user for input
	terminal_color = make_color(COLOR_RED, COLOR_BLACK);
	print("cosh -> ");
	terminal_color = make_color(COLOR_GREEN, COLOR_BLACK);
   // Start listening for keyboard input
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
						//if (histLoc > 0) {histLoc--;updateInLineToHistory();}
					} else if (ch == -4) {
						//if (histLoc < arraylen(inputHist)) {histLoc++;updateInLineToHistory();}
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


// The starting point of the high level kernel
extern "C" void kernel_main(void) {
   // Designed to init into terminal for now.
	terminalKernel();
	//graphicalKernel();
}
