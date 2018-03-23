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

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// Define string type
typedef char* string;

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

// Get the length of a string
size_t strlen(const char* str) {
	size_t ret = 0;
	while ( str[ret] != 0 )
	ret++;
	return ret;
}

// Get the length of an array of strings
int arraylen (char** array) {
	int ret = -1;
	for (int itemNo = 0; array[itemNo] != 0x00; itemNo++) {
		ret++;
	}
	return ret+1;
}

// Determine whether one string is equal to another
bool strEqual (const char* str1, const char* str2) {
	bool returner = true;
   int ptr = 0;
	while (str1[ptr]!=0x00 && str2[ptr]!=0x00) {
      if (str1[ptr]!=str2[ptr]) {
         returner = false;
      }
      ptr++;
   }
   if (!(str1[ptr]==0x00 && str2[ptr]==0x00)) {
      returner = false;
   }

	return returner;
}

// Determine the index (if any) of an item within an array
int contains (char** array, char* str) {
	for (int itemNo = 0; array[itemNo] != 0x00; itemNo++) {
		if (strEqual (array[itemNo], str)) {
			return itemNo;
		}
	}
	return -1;
}

// Get a byte of input
static inline uint8_t inb (uint16_t port) {
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

// Set a byte of output
static inline void outb( unsigned short port, unsigned char val ) {
	asm volatile("outb %0, %1" : : "a"(val), "Nd"(port) );
}

// Switch into real mode (not working)
static inline void changeToRealMode () {
	asm (
			 "idt_real:\n\t"
			 "	dw $0x3ff\n\t"
			 "	dd $0\n\t"

			 "savcr0:\n\t"
			 "	dd $0\n\t"

			 "Entry16:\n\t"

			 "	cli\n\t"
			 "	mov %eax, DATASEL16\n\t"
			 "	mov %ds, %eax\n\t"
			 "	mov %es, %eax\n\t"
			 "	mov %fs, %eax\n\t"
			 "	mov %gs, %eax\n\t"
			 "	mov %ss, %eax\n\t"

			 "	mov %eax, %cr0\n\t"
			 "	mov [savcr0], %eax\n\t"
			 "	and %eax, $0x7FFFFFFe\n\t"
			 "	mov %cr0, %eax\n\t"

			 //"	jmp 0 :GoRMode\n\t"

			 //"GoRMode:\n\t"
			 "	mov %sp, $0x8000\n\t"
			 "	mov %ax, $0\n\t"
			 "	mov %ds, %ax\n\t"
			 "	mov %es, %ax\n\t"
			 "	mov %fs, %ax\n\t"
			 "	mov %gs, %ax\n\t"
			 "	mov %ss, %ax\n\t"
			 "	lidt idt_real\n\t"
			 "	sti");
}

// Switch into protected mode (not working)
static inline void changeToProtectedMode () {
	asm ("cli          \n\t"
			 "lgdt gdtr  \n\t"
			 "mov %eax, %cr0 \n\t"
			 "or %al, $1     \n\t"
			 "mov %cr0, %eax");
}

// Header declarations for various print functions
void println(const char* data);
void print(const char* data);
void tPutChar(const char data);

// ========== Memory Functions ========== //
void* latestFree = (void*) 0xCDCDCDCD;

void* findFreeBlock (int size) {

	void* startPointer = latestFree;
	bool hasFoundFreeMemory = true;

	while (!hasFoundFreeMemory) {
		while (&startPointer != NULL) {
			startPointer += 0x01;
			print ((char*) &startPointer);
		}
		hasFoundFreeMemory = true;
		for (void* i = startPointer; i < (void*) 0xFDFDFDFD; i++) {
			if (i != NULL) {
				hasFoundFreeMemory = false;
				break;
			}
		}
		//if (hasFoundFreeMemory) {println ("Found free memory!");} else {println ("Not large enough");}
	}
	latestFree += size;
	return startPointer;
}

void* memset(void* b, int c, size_t len) {
    char* p = (char*)b;
    for (size_t i = 0; i != len; ++i) {
        p[i] = c;
    }
    return b;
}

void* malloc (int size) {
	void* freeBlock = findFreeBlock (size);
	return freeBlock;
}

void* calloc (int size) {
	void* b = malloc (size);
	memset (b, 0x00, size);
	return b;
}

void freeSomeMemory () {
	// for (void* i = (void*) 0xCDCDCD; i < (void*) 0x51200000; i++) {
	// 	(int *) i = NULL;
	// }
}

void free (void *ptr) {}

void *operator new(size_t size) {
    return malloc(size);
}

void *operator new[](size_t size) {
    return malloc(size);
}

void operator delete(void *p) {
    free(p);
}

void operator delete[](void *p) {
    free(p);
}

// ==========     ========== //

// Get the nth item of a string, splitting at a delimiter (now deprecated, because it's wildly inefficient)
string getNthItemOf (string str, char delim, int item) {
	int itemNo = 0;
	string returner;
	int secondLoc = 0;
	int characterPtr = 0;
	while (itemNo <= item) {
		if (str[characterPtr] == delim) {
			itemNo++;
		}
		characterPtr++;
	}
	while (str[characterPtr] != delim) {
		returner[secondLoc] = str[characterPtr];
		characterPtr++;
		secondLoc++;
	}
}

// Split a string into an array of strings at a delimiter
// TODO: Fix this
void splitStr(const char* str, const char d, char** into) {
    if(str != NULL && into != NULL) {
        int n = 0;
        int c = 0;
        for(int i = 0; str[c] != '\0'; i++,c++) {
            into[n][i] = str[c];
            if(str[c] == d) {
                into[n][i] = '\0';
                i = -1;
                n++;
            }
        }
    }
}

// Allocate items in an array (seems like bullshit)
void allocarr(char** pointers, int bytes, int slots) {
    int i = 0;
    while(i <= slots) {
        pointers[i] = (char*)calloc(bytes);
        i++;
    }
}
