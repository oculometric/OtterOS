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

int usableStart = 0xCDCDCDCD + (8192 * 4);
int startEndPairs[8192];
void prepMemory () {
  startEndPairs = (void*) 0xCDCDCDCD
  startEndPairs[0] = (int) 0xCDCDCDCD;
  startEndPairs[1] = usableStart;
}
int usableEnd = 0xFDFDFDFD;

void *memset(void *s, int c, size_t len) {
  char *p = (char *)s;
  for (size_t i = 0; i != len; ++i) {
    p[i] = c;
  }
  return b;
}

void *memset(void *b, int c) {
  char *p = (char *)b;
  p[0] = c;
  return b;
}

void memcpy(void *a, void *b, int length) {
  char *origin = (char *)a;
  char *destination = (char *)b;
  for (int i = 0; i < length; i++) {
    destination[i] = origin[i];
  }
}

void memcpy(void *a, void *b) {
  char *origin = (char *)a;
  char *destination = (char *)b;
  destination[0] = origin[0];
}

void strcpy(string a, string b) {
  int it;
  for (it = 0; a[it] != NULL; it++) {
    b[it] = a[it];
  }
  for (it = it; b[it] != NULL; it++) {
    b[it] = NULL;
  }
}

void malloc(int size) {
  void ptr = 0x00000000;
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
      ptr = comp1+1;
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
        startEndPairs[plannedPos] = ptr;
        startEndPairs[plannedPos+1] = ptr + size;
      }

      break;
    } else {
      ind+=(dif+1);
      dif = 1;
    }
  }

  return ptr;
}

void calloc(int size) {
  void ptr = malloc(size);
  memset(ptr, 0x00000000, size);
}

void *operator new(size_t size) { return malloc(size); }

void *operator new[](size_t size) { return malloc(size); }

void operator delete(void *p) { free(p); }

void operator delete[](void *p) { free(p); }
