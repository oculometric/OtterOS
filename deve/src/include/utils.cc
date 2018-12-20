/* # Utils.cc #
 *
 * ## Description ##
 * Contains various utility functions and declarations for
 * other parts of the project to use.
 *
 * ## Info ##
 * Created 12/03/18
 * Format C++ source
 * Written by JavaxCosten
 *
 * ## Copyright ##
 * Copyright (C) 2018 OtterOS Project - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the LICENSE, found in the top level directory.
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

char intstrings[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

// Get the length of a string
size_t strlen(const char *str) {
	size_t ret = 0;
	while (str[ret] != 0)
		ret++;
	return ret;
}

size_t strlen(string str) {
	size_t ret = 0;
	while (str[ret] != 0)
		ret++;
	return ret;
}

string appendChar(char c, string s) {
	return s + c;
}

string putDigitTo(int x, string out) {
	string tmp = out;
	if (x >= 10) {
		tmp = putDigitTo(x / 10, tmp);
	}
	int digit = x % 10;
	char dig = intstrings[digit];
	return appendChar(dig, tmp);;
}

string intToString (int i) {
	string out = "";
	return putDigitTo(i, out);
}

// Define a bunch of colour constants
enum vga_color {
  COLOR_BLACK = 0,
  COLOR_BLUE = 1,
  COLOR_GREEN = 2,
  COLOR_CYAN = 3,
  COLOR_RED = 4,
  COLOR_MAGENTA = 5,
  COLOR_BROWN = 6,
  COLOR_LIGHT_GREY = 7,
  COLOR_DARK_GREY = 8,
  COLOR_LIGHT_BLUE = 9,
  COLOR_LIGHT_GREEN = 10,
  COLOR_LIGHT_CYAN = 11,
  COLOR_LIGHT_RED = 12,
  COLOR_LIGHT_MAGENTA = 13,
  COLOR_LIGHT_BROWN = 14,
  COLOR_WHITE = 15,
};

// Generate foreground/background pair
uint8_t make_color(enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4;
}

// Generate a VGA entry from a colour and a character
uint16_t make_vgaentry(char c, uint8_t color) {
  uint16_t c16 = c;
  uint16_t color16 = color;
  return c16 | color16 << 8;
}

// Get the length of an array of strings
int arraylen(char **array) {
  int ret = -1;
  for (int itemNo = 0; array[itemNo] != 0x00; itemNo++) {
    ret++;
  }
  return ret + 1;
}

// Determine whether one string is equal to another
bool strEqual(const char *str1, const char *str2) {
  bool returner = true;
  int ptr = 0;
  while (str1[ptr] != 0x00 && str2[ptr] != 0x00) {
    if (str1[ptr] != str2[ptr]) {
      returner = false;
    }
    ptr++;
  }
  if (!(str1[ptr] == 0x00 && str2[ptr] == 0x00)) {
    returner = false;
  }

  return returner;
}

int contains(char **array, char *str) {
  for (int itemNo = 0; array[itemNo] != 0x00; itemNo++) {
    if (strEqual(array[itemNo], str)) {
      return itemNo;
    }
  }
  return -1;
}

// Determine the index (if any) of an item within an array
int contains(const char **array, char *str) {
  for (int itemNo = 0; array[itemNo] != 0x00; itemNo++) {
    if (strEqual(array[itemNo], str)) {
      return itemNo;
    }
  }
  return -1;
}

// Get a byte of input
static inline uint8_t inb(uint16_t port) {
  uint8_t ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

// Set a byte of output
static inline void outb(unsigned short port, unsigned char val) {
  asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline void realBad () {
	log ("Going into real mode...");
	asm (R"(idt_real:
		.word 0x3ff
		.int 0
		cli
		mov %cr0, %eax
		and 0x7ffffffe, %eax
		mov %eax, %cr0


		GoRMode:
		mov $0x8000, %sp
		mov $0, %ax
		mov %ax, %ds
		mov %ax, %es
		mov %ax, %fs
		mov %ax, %gs
		mov %ax, %ss
		lidt idt_real
		sti  )");
		log ("Done");
	}

static inline void protectedBad () {
	log ("Going back into protected...");
	asm (R"(cli
		#lgdt (gdtr)
		mov %cr0, %eax
		or 1, %al
		mov %eax, %cr0
		jmp PModeMain

		PModeMain:
		# load DS, ES, FS, GS, SS, ESP)");
	log ("Done");
}

// Switch into real mode (not working)
static inline void changeToRealMode() {
  asm(R"(idt_real:
					.word 0x3ff
					.int 0
				savcr0:
      		.int 0
				Entry16:
					cli
					mov DATASEL16, %eax
					mov %eax, %ds
      		mov %eax, %es
      		mov %eax, %fs
      		mov %eax, %gs
      		mov %eax, %ss

      		mov %cr0, %eax
      		mov %eax, (savcr0)
      		and $0x7FFFFFFe, %eax
      		mov %eax, %cr0

      		jmp GoRMode

      	GoRMode:
      		mov $0x8000, %sp
      		mov $0, %ax
      		mov %ax, %ds
      		mov %ax, %es
      		mov %ax, %fs
      		mov %ax, %gs
      		mov %ax, %ss
      		lidt idt_real
      		sti
				)");
				log ("WE DID IT OMG");
}

// Switch into protected mode (not working)
static inline void changeToProtectedMode() {
  asm("cli          \n\t"
      "lgdt gdtr  \n\t"
      "mov %eax, %cr0 \n\t"
      "or %al, $1     \n\t"
      "mov %cr0, %eax");
}

#define PORT 0x3f8 /* COM1 */

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
  while (is_transmit_empty() == 0)
    ;

  outb(PORT, a);
}

void log(string s) {
  for (int i = 0; s[i] != NULL; i++) {
    write_serial(s[i]);
  }
  write_serial(0x0A);
}

void logChar (char c) {
	write_serial(c);
	write_serial(0x0A);
}

void log(const char* s) {
  for (int i = 0; s[i] != NULL; i++) {
    write_serial(s[i]);
  }
  write_serial(0x0A);
}

void logInt (int i) {
	//char* s = intToString(i); log ("Errm"); log(s);
  logChar (intstrings[i]);
}

void logHex (int i) {
	char* buffer = (char*) i;
	int numBytes = strlen (buffer);
	char s[numBytes*2+1];
	const char* pHexTable="0123456789ABCDEF";
	int iPos=0;

	for(int i=0; i<numBytes; i++){
		//assume buffer contains some binary data at this point
		const char cHex=buffer[i];
		s[iPos++]=pHexTable[(cHex>>4)&0x0f];
		s[iPos++]=pHexTable[cHex&0x0f];
	}
	s[iPos]='\0';
	log(s);
}

//Log that a fatal error occurred
//TODO: Add exit functionality
void fatal (string msg) {
  log ("==========FATAL==========");
  log (msg);
  log ("=========================");
	shouldContinue = false;
}

// Log a warning
void warn (string msg) {
  log ("==========WARNING==========");
  log (msg);
  log ("===========================");
}


// Split a string into an array of strings at a delimiter
void splitStr(const char *str, const char d, char **into) {
  if (str != NULL && into != NULL) {
    int n = 0;
    int c = 0;
    for (int i = 0; str[c] != '\0'; i++, c++) {
      into[n][i] = str[c];
      if (str[c] == d) {
        into[n][i] = '\0';
        i = -1;
        n++;
      }
    }
  }
}

// Allocate items in an array (is bullshit)
void allocarr(char **pointers, int bytes, int slots) {
  int i = 0;
  while (i <= slots) {
    pointers[i] = (char *)calloc(bytes);
    i++;
  }
}

// define our structure
typedef struct __attribute__ ((packed)) {
    unsigned short di, si, bp, sp, bx, dx, cx, ax;
    unsigned short gs, fs, es, ds, eflags;
} regs16_t;
