/* # Globals.cc #
 *
 * ## Description ##
 * Contains declarations for the global variable system (much
 * like the variable system in bash).
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

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

char* names[256];
char* values[256];

char* getGlobal (char* key) {
  int contain = contains (names, key);
  if (contain != -1) {
    return values[contain];
  }
  return "";
}

void setGlobal (char* key, char* value) {
  int contain = contains (names, key);
  if (contain != -1) {
    strcpy (value, values[contain]);
  } else {
    int len = arraylen (names);
    strcpy (key, names[len]);
    strcpy (key, values[len]);
  }
}

void setupGlobals () {
for (int a=0;a<255;a++) {
	for (int b=0;b<64;b++) {names[a][b] = 0x00;}
	for (int c=0;c<256;c++) {values[a][c] = 0x00;}
}

  setGlobal ("meshv", "0.2");
}
