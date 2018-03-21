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

char* names[255] = {"coshv", "bootmode"};
char* values[255] = {"0.1", "graphics"};

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
    values[contain] = value;
  } else {
    int len = arraylen (names);
    names [len] = key;
    values [len] = key;
  }
}
