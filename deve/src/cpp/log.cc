/* # Log.cc #
 *
 * ## Description ##
 * Declares logging-related util functions
 *
 * ## Info ##
 * Created 23/12/18
 * Format C++ source
 * Written by JavaxCosten
 *
 * ## Copyright ##
 * Copyright (C) 2018 OtterOS Project - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the LICENSE, found in the top level directory.
 */
#include "declarations.h"

#define PORT 0x3f8 /* COM1 */

// Get a byte of input
uint8_t inb(uint16_t port) {
  uint8_t ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

// Set a byte of output
void outb(unsigned short port, unsigned char val) {
  asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

void init_serial() {
  outb(PORT + 1, 0x00); // Disable all interrupts
  outb(PORT + 3, 0x80); // Enable DLAB (set baud rate divisor)
  outb(PORT + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
  outb(PORT + 1, 0x00); //                  (hi byte)
  outb(PORT + 3, 0x03); // 8 bits, no parity, one stop bit
  outb(PORT + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
  outb(PORT + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

int is_transmit_empty() { return inb(PORT + 5) & 0x20; }

void write_serial(char a) {
  while (is_transmit_empty() == 0);
  outb(PORT, a);
}

void log(char *s) {
  for (int i = 0; s[i] != NULL; i++) {
    write_serial(s[i]);
  }
  write_serial(0x0A);
}

void logChar (char c) {
	write_serial(c);
	write_serial(0x0A);
}

void logInt (int i) {
	char s[64];
	intToString(s, i, 10);
  log (s);
}

void logHex (int i) {
	char s[64];
	intToString(s, i, 16);
	log(s);
}

//Log that a fatal error occurred
void fatal (char *msg) {
  log ("==========FATAL==========");
  log (msg);
  log ("=========================");
	//shouldContinue = false;
}

// Log a warning
void warn (char *msg) {
  log ("==========WARNING==========");
  log (msg);
  log ("===========================");
}
