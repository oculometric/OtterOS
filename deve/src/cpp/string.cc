/* # String.cc #
 *
 * ## Description ##
 * Declares string-related util functions
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

int strlen (char *s) { // Determine the length of a string
	int ret = 0;
	while (str[ret] != 0)
		ret++;
	return ret;
}

int strcmp (const char *dst char *src) {
	int i = 0;
	while (dst[i] == src[i]) {
		if (src[i++] == '\0') return true;
	}
	return false;
}

void strcpy (char *dst, const char *src) {
	int i = 0;
	while (dst[i] = src[i++]);
	//return i;
}

void strcat (char *dest, const char *src) {
	char *destStart = (char*) ((int)dest+strlen(dest));
	memcpy(destStart, src, stlen(src));
}

void strncpy (char *destString, const char *sourceString, int maxLength) {
	int i = 0;
	while ((i < maxLength) && (sourceString[i] != '\0')) {
		dst[i] = src[i++];
	}
}

bool strncmp (const char *s1, const char *s2, int c) {
	int i = 0;
	while (dst[i] == src[i++]) {
		if (i == c) return true;
	}
	return false;
}
