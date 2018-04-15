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
#include "include/declarations.h"
#include "include/memory.cc"
#include "include/utils.cc"
#include "include/globals.cc"
#include "include/terminal.cc"
#include "include/mesh.cc"
#include "include/graphicKernel.cc"
#include "include/kbdus.h"
#include "include/usqwerty.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Define keyboard inputs
#define PIC1 0x20
#define PIC2 0xA0

#define ICW1 0x11
#define ICW4 0x01
// TODO: Move this into a class
// Set up the keyboard
void init_pics(int pic1, int pic2) {
  /* send ICW1 */
	log ("Initialising PICs for keyboard input...");
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
	log ("Done");
}

bool isWaitingForUp = false;

bool shift = false;

char downChar = '\0';
bool latestCharWasCharUp = false;

void doChars () {
  //while (shouldContinue) {
	log ("Doing chars...");
	//log (downChar);
  if (downChar == '\n') {
		log ("downChar was newline");
    println("");
    log(currentInLine);
    if (strlen(currentInLine) > 0) {
      executeLine();
    } else {
      displayPrompt();
    }
  } else if (downChar == '\b') {
		log ("downChar was delete");
    tDeleteChar();
  } else if (downChar == -1) {
		log ("downChar was escape");
    shouldContinue = false;
  } else if (downChar == 0x00) {log ("downChar was NULL????");} else {
		log ("downChar was a normal char");
    currentInLine[terminal_column - 8] = downChar;
    tPutChar(downChar);
  }
//}
log ("Done");
}

// char waitForScanCode() {
//   while (!(inb(0x64) & 1)) {doChars();}
//   char in = inb (0x60);
//   if (in & 0x2A) {
//     shift = true;
//   }
//   return in;
// }

char characterOf (char c) {
  if (!shift) {
    return lowercase2[c];
  } else {
    return NULL;
  }
}

// void oldCode (char c) {
//   if (inb(0x60) != c) {
//     c = inb(0x60);
//     if (c > 0) {
//       int a = c;
//       char ch = ' ';
//       if (a == 0x2A) {
//         leftShiftDown = !leftShiftDown;
//       } else if (a == 0x36) {
//         rightShiftDown = !rightShiftDown;
//       } else {
//         ch = normalmap[a];
//         if (rightShiftDown || leftShiftDown) {
//           ch = shiftmap[a];
//         }
//         if (ch == '\n') {
//           println("");
//           log(currentInLine);
//           if (strlen(currentInLine) > 0) {
//             executeLine();
//           } else {
//             displayPrompt();
//           }
//         } else if (ch == '\b') {
//           tDeleteChar();
//         } else if (ch == -1) {
//           if (terminal_column > 8) {
//             terminal_column--;
//           }
//           updateCursorLocation();
//         } else if (ch == -2) {
//           if (terminal_column < VGA_WIDTH) {
//             terminal_column++;
//           }
//           updateCursorLocation();
//         } else if (ch == -3) {
//           // if (histLoc > 0) {histLoc--;updateInLineToHistory();}
//         } else if (ch == -4) {
//           // if (histLoc < arraylen(inputHist))
//           // {histLoc++;updateInLineToHistory();}
//         } else {
//           currentInLine[terminal_column - 8] = ch;
//           tPutChar(ch);
//         }
//       }
//     }
//   }
// }

// Terminal based kernel
void terminalKernel() {
  // Set up the terminal environment
	log ("Setting up terminal environment...");
  tInitialize();
	log ("Done");

  // Prompt the user for input
  displayPrompt();

  // Start listening for keyboard input
	log ("Starting keypress listener...");
	warn ("Keypress listener is not working, keypresses are not detected/reacted to");
  //char c = 0;
  init_pics(0x20, 0x28);
	//fatal ("No point in continuing, input doesn't work");
	char c = 0;
	while (shouldContinue) {
		c = inb (0x60);
		log ("Took input");
		if (c > 0 && characterOf(c) != 0) {
			log ("Validated input");
			if (c & 0xF0) {
				downChar = 0;
			} else {
				log ("Charing input");
				char c = characterOf(c);
				downChar = c;
				doChars();
			}
		}
	}
}

// The starting point of the high level kernel
extern "C" void kernel_main(void) {
  // Designed to init into terminal for now.
	log ("Preparing memory manager...");
  prepMemory();
	log ("Done");
	log ("Setting up global variables...");
	setupGlobals();
	log ("Done");
	log ("Starting terminal kernel...");
  terminalKernel();
	log ("Finished");
	log ("=========TERMINATE=========");
  // graphicalKernel();
}
