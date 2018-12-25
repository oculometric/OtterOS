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
