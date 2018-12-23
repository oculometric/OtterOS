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

bool shouldContinue = true;

void intToString (char *buf, unsigned long int n, int base);

void memset(char *dest, char src);
void memset(char *dest, char src, int len);
void memcpy(char *dest, char *src, int length);

int strlen (char *s);
bool strcmp (const char *dst, char *src);
void strcpy (char *dst, const char *src);
void strcat (char *dest, const char *src);
void strncpy (char *destString, const char *sourceString, int maxLength);
bool strncmp (const char *s1, const char *s2, int c);

void logChar (char c);
void logInt (int i);
void logHex (int i);
void log (char *s);

void sleep (int delay);

void fatal (char *msg);
void warn (char *msg);

class OtterKernel {
public:
	void prepare ();
}
