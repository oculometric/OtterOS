// Define keyboard inputs

#include "usqwerty.h"
#include "declarations.h"

#define PIC1 0x20
#define PIC2 0xA0

#define ICW1 0x11
#define ICW4 0x01

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
char oldChar = '\0';

char characterOf (char c) {
  if (!lshift && !rshift) {
    return lowercase1[c];
  } else {
    return uppercase1[c];
  }
}

void prepareKeyboard () {
  // Set up the terminal environment
  log ("Setting up terminal environment...");
  //t.tInitialize();
  log ("Failed");
  fatal ("Terminal environment setup failed, terminal not implemented!");

  // Prompt the user for input
  //displayPrompt();
  fatal ("Prompt was not displayed, all will fail!");

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
}

// Returns a character if a key is pressed, otherwise 0x00
char update () {
  char code = 0;
  code = inb (0x60);
  char cc = characterOf(code);
  oldChar = downChar;
  if ((code & 128) != 128) {
    if (downChar == -3) {
      rshift = true;
      downChar = 0x00;
    } else if (downChar == -4) {
      lshift = true;
      downChar = 0x00;
    } else {
      downChar = cc;
    }
  } else {
    if (code == 0xB6) {
      rshift = false;
    } else if (code = 0xAA) {
      lshift = false;
    }
    downChar = 0x00;
  }

  if (downChar != 0x00 && !isWaitingForUp) {
    return downChar;
    isWaitingForUp = true;
  } else if (isWaitingForUp && oldChar != downChar) {
    isWaitingForUp = false;
  }
  return 0x00;
}
