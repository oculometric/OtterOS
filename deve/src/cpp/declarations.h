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
void * calloc (int size);
void * malloc (int size);
void free (void * p);

void * operator new(size_t size);
void * operator new[](size_t size);
void operator delete(void *p);
void operator delete[](void *p);

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
void logChar (char c); // Need fixing
void logInt (int i); //
void logHex (int i); //
void log (char *s); //
void fatal (char *msg);
void warn (char *msg);

// modectl.cc
void switchToRealMode (); // Need implementing
void switchToProtectedMode (); //
void executeFunctionInProtectedMode (void *func, int functionByteLength); //

// time.cc
void sleep (int delay);

// otterKernel.cc
class OtterKernel {
public:
	void prepare ();
};
