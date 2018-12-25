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
#include "declarations.h"

void intToString (char *buf, unsigned long int n, int base) {
	unsigned long int tmp;
	int i, j;
	tmp = n;
	i = 0;

	do {
		tmp = n % base;
		buf[i++] = (tmp < 10) ? (tmp + '0') : (tmp + 'a' - 10);
	} while (n /= base);
	buf[i--] = 0;

	for (j = 0; j < i; j++, i--) {
		tmp = buf[j];
		buf[j] = buf[i];
		buf[i] = tmp;
	}
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

int contains(char **array, char *str) {
  for (int itemNo = 0; array[itemNo] != 0x00; itemNo++) {
    if (strcmp(array[itemNo], str)) {
      return itemNo;
    }
  }
  return -1;
}

// Determine the index (if any) of an item within an array
int contains(const char **array, char *str) {
  for (int itemNo = 0; array[itemNo] != 0x00; itemNo++) {
    if (strcmp(array[itemNo], str)) {
      return itemNo;
    }
  }
  return -1;
}

static inline void realBad () {
	logLn ("Going into real mode...");
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
		logLn ("Done");
	}

static inline void protectedBad () {
	logLn ("Going back into protected...");
	asm (R"(cli
		#lgdt (gdtr)
		mov %cr0, %eax
		or 1, %al
		mov %eax, %cr0
		jmp PModeMain

		PModeMain:
		# load DS, ES, FS, GS, SS, ESP)");
	logLn ("Done");
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
				logLn ("WE DID IT OMG");
}

// Switch into protected mode (not working)
static inline void changeToProtectedMode() {
  asm("cli          \n\t"
      "lgdt gdtr  \n\t"
      "mov %eax, %cr0 \n\t"
      "or %al, $1     \n\t"
      "mov %cr0, %eax");
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
