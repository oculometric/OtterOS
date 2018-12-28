/* # Declarations.h #
 *
 * ## Description ##
 * Declares any functions (mostly logging etc)
 * for the program to be able to use.
 *
 * ## Info ##
 * Created 29/03/18
 * Format C++ header
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

//bool shouldContinue = true;

// utils.cc
void intToString (char *buf, unsigned long int n, int base);

// memory.cc
void memset(char *dest, char src);
void memset(char *dest, char src, int len);
void memcpy(char *dest, char *src, int length);
void * calloc (size_t size);
void * malloc (size_t size);
void free (void * p);
void prepMemory ();

void * operator new(size_t size);
void * operator new[](size_t size);
void operator delete(void *p);
void operator delete[](void *p);

void logAllocationTable ();

// string.cc
int strlen (char *s);
int strcmp (const char *s1, char *s2);
void strcpy (char *dst, const char *src);
void strcat (char *dest, const char *src);
void strncpy (char *destString, const char *sourceString, int maxLength);
bool strncmp (const char *s1, const char *s2, int c);

// log.cc
void init_serial ();
void outb(unsigned short port, unsigned char val);
uint8_t inb(uint16_t port);
void logChar (char c);
void logInt (long int i);
void logHex (int i);
void logLn (char *s);
void logBool (bool b);
void log (char *s);
void fatal (char *msg);
void warn (char *msg);

// modectl.cc
void switchToRealMode (); // Need implementing
void switchToProtectedMode (); //
void executeFunctionInProtectedMode (void *funcStart, char funcEndChar); //

// time.cc
void sleep (int delay);

// otterKernel.cc
class OtterKernel {
public:
	void prepare ();
  void memoryTest();
};


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

// terminaloutput.cc and terminalinput.cc
class Terminal {
public:
  void print (const char *s);
  void println (const char *s);
  void deleteChars (int num);
  void deleteLines (int num);
  void setActiveStyleFlag (char flag);
  uint8_t make_color(enum vga_color fg, enum vga_color bg);
  void resetTerminal ();
private:
  void appendChar (char c);
  void moveToNextLine ();
  uint16_t *videoMemStart = (uint16_t *)0xB8000;
  char activeStyleFlag = 0x07;
  int terminal_row = 0;
	int terminal_column = 0;
  static const size_t VGA_WIDTH = 80;
	static const size_t VGA_HEIGHT = 25;

  uint16_t make_vgaentry(char c, uint8_t color);
  void updateCursorLocation ();
};
