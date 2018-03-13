/* Copyright (C) 2018 JavaxCosten - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the LICENSE, found in the top level directory.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

char* names[255] = {"coshv", "bootmode"};
char* values[255] = {"0.1", "graphics"};

char* getValueForKey (char* key) {
  int contain = contains (names, key);
  if (contain != -1) {
    return values[contain];
  }
  return "";
}
