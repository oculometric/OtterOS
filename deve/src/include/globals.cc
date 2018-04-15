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
	log ("Looking for global variable with specified name...");
  int contain = contains (names, key);
	log ("Done");
  if (contain != -1) {
		log ("Found one! Returning value");
    return values[contain];
  }
	log ("We didn't find anything");
  return "";
}

void setGlobal (char* key, char* value) {
	log ("Looking for global variable with specified name...");
  int contain = contains (names, key);
	log ("Done");
  if (contain != -1) {
		log ("Found one! Copying specified value into space...");
    strcpy (value, values[contain]);
		log ("Done");
  } else {
		log ("We couldn't find the variable, so we'll create a new one");
    int len = arraylen (names);
		log ("Copying name and value into new space...");
    strcpy (key, names[len]);
    strcpy (key, values[len]);
		log ("Done");
  }
}

void setupGlobals () {
	log ("Preparing globals");
	log ("Spacing memory...");
	for (int a=0;a<255;a++) {
		for (int b=0;b<64;b++) {names[a][b] = 0x00;}
		for (int c=0;c<256;c++) {values[a][c] = 0x00;}
	}
	log ("Done");
	log ("Setting preset variable(s)...");
  setGlobal ("meshv", "0.2");
	log ("Done");
}
