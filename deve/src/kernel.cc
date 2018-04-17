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
#include "include/time.cc"
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

bool rshift = false;
bool lshift = false;

char downChar = '\0';
bool latestCharWasCharUp = false;

void doChars () {
	log ("Doing chars...");
  if (downChar == '\n') {
    println("");
    log(currentInLine);
    if (strlen(currentInLine) > 0) {
      executeLine();
    } else {
      displayPrompt();
    }
  } else if (downChar == '\b') {
    tDeleteChar();
  } else if (downChar == -1) {
    shouldContinue = false;
  } else if (downChar == -3) {
    rshift = true;
  } else if (downChar == -4) {
    lshift = true;
  } else if (downChar == 0x00) {
	} else if (downChar > 0) {
    currentInLine[terminal_column - 8] = downChar;
    tPutChar(downChar);
  }
	log ("Done");
}

char characterOf (char c) {
  if (!lshift && !rshift) {
    return lowercase1[c];
  } else {
    return NULL;
  }
}

// char upCharacterOf (char c) {
// 	if (!shift) {
//     return lowercase1[c];
//   } else {
//     return NULL;
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
  init_pics(0x20, 0x28);
	outb(0x60, 0xF0);
	while (inb(0x60) != 0xFA);
	outb(0x60, 0);
	while (inb(0x60) != 0xFA);

	log ("Set keyboard scan code set to 1");

	outb(0x60, 0xF3);
	while (inb(0x60) != 0xFA);
	outb(0x60, 0x7F);
	while (inb(0x60) != 0xFA);

	log ("Finshed keyboard setup");
	log ("Done");

	char code = 0;
	while (shouldContinue) {
		code = inb (0x60);
		char cc = characterOf(code);
		if ((code & 128) != 128) {
			log (code);
			downChar = cc;
		} else {
			if (cc == -3) {
				rshift = true;
			} else if (cc == -4) {
				lshift = true;
		 	}
		 downChar = 0x00;
	 }

		if (downChar != 0x00) {
			log (downChar);
			doChars();
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
