/* # Memory.cc #
 *
 * ## Description ##
 * Memory allocation and deallocation functions.
 *
 * ## Info ##
 * Created 17/03/18
 * Format C++ source
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

#include "declarations.h"

void memset(char *dest, char src, int len) {
	char *p = dest;
  while (len--) {
    *p++ = src;
  }
}

void memset(char *dest, char src) {
  *b = src;
}

void memcpy(char *dest, char *src, int length) {
	char *p = dest;
	while (length--) {
		*p++ = *src++;
	}
}

int usableStart = 0xCDCDCDCD + (8192 * 4);
int startEndPairs[8192];
void prepMemory () {
  //startEndPairs = (void*) 0xCDCDCDCD;
  startEndPairs[0] = (int) 0xCDCDCDCD;
  startEndPairs[1] = usableStart;
}
int usableEnd = 0xFDFDFDFD;

void* malloc(int size) {
  void* ptr = 0x00000000;
  int ind = 1;
  int dif = 1;
  while (true) {
    int comp1 = startEndPairs[ind];
    int comp2 = startEndPairs[ind+dif];
    while (comp2 == 0 && (dif + ind < 8192)) {
      dif++;
      comp2 = startEndPairs[ind+dif];
    }
    if (dif + ind >= 8192) {
      ptr = 0x0;
      break;
    }
    if ((comp2 - comp1) > size) {
      ptr = (void*)comp1+1;
      int plannedPos = ind+1;
      if (startEndPairs[plannedPos] != 0x0) {
        int tmpa = startEndPairs[plannedPos];
        int tmpb = startEndPairs[plannedPos+1];

        for (int i = plannedPos+2; i <= 8190; i++) {
          int tmpc = tmpa;
          tmpa = tmpb;
          tmpb = startEndPairs[i];
          startEndPairs[i] = tmpc;
        }
      } else {
        startEndPairs[plannedPos] = (int) ptr;
        startEndPairs[plannedPos+1] = (int) ptr + size;
      }

      break;
    } else {
      ind+=(dif+1);
      dif = 1;
    }
  }

  return ptr;
}

void* calloc(int size) {
  void* ptr = malloc(size);
  memset(ptr, 0x00000000, size);
	return ptr;
}

void free (void* p) {}

void *operator new(size_t size) { return malloc(size); }

void *operator new[](size_t size) { return malloc(size); }

void operator delete(void *p) { free(p); }

void operator delete[](void *p) { free(p); }
