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
 #include "declarations.h"

void memset(char *dest, char src, int len) {
	char *p = dest;
  while (len--) {
    *(p++) = src;
  }
}

void memset(char *dest, char src) {
  *dest = src;
}

void memcpy(char *dest, char *src, int length) {
	char *p = dest;
	while (length--) {
		*(p++) = *(src++);
	}
}

unsigned char *usableStart = (unsigned char *) 0x00100000;
unsigned char *usableEnd = (unsigned char *) 0x00EFFFFF;
unsigned char *allocationStart;

size_t totalSize = usableEnd-usableStart;

void prepMemory () {

  allocationStart = usableStart+1;
  logLn ("memset is failing");
  memset((char *)usableStart, 0x00000000, usableEnd-usableStart);
  // memset((char *)usableStart, 0xCCCCCCCC);
  // memset((char *)usableEnd,   0xCCCCCCCD);
}

void * find (void *start, void *end, int findValue) {
  while (start < end) {
    if (*((char *)start) == findValue) {
      return start;
    }
    start++;
  }
  return (void *)0xCDCDCDCD;
}

void * findNextFreeAllocationSpace (void *start) {
  while ((*((char *)start) != 0x0) && start < usableEnd) {
    start = find (start, usableEnd, 0xCCCCCCCD);
    if (start == (void *)0xCDCDCDCD) {
      logLn ("Could not find another end spacer!");
      return start;
    }
    start++;
  }
  return start;
}

void * malloc (size_t size) {
  void *startPtr = allocationStart;
  void *emptyEnd = find (startPtr, usableEnd, 0xCCCCCCCC);
  if (emptyEnd == (void *)0xCDCDCDCD) {
    return startPtr;
  }
  while ( (((char *)emptyEnd)-((char *)startPtr) < size) && ((startPtr + size) < usableEnd) ) {
    startPtr = findNextFreeAllocationSpace (find (startPtr+1, usableEnd, 0xCCCCCCCD));
    emptyEnd = find (startPtr, usableEnd, 0xCCCCCCCC);
    if (emptyEnd == (void *)0xCDCDCDCD) {
      emptyEnd = usableEnd;
    }
  }

  return startPtr;
}

void * calloc(size_t size) {
  void *ptr = malloc(size);
  memset((char *)ptr, 0x00000000, size);
	return ptr;
}

void free (void *p) {
  void *currentAllocationEnd = find (p, usableEnd, 0xCCCCCCCD);
  int size = ((char *)currentAllocationEnd)-((char *)p);
  memset(((char *)p)-1, 0x00000000, size);
}

// void * malloc(int size) {
//   void *ptr = 0x00000000;
//   int ind = 1;
//   int dif = 1;
//   while (true) {
//     int comp1 = startEndPairs[ind];
//     int comp2 = startEndPairs[ind+dif];
//     while (comp2 == 0 && (dif + ind < 8192)) {
//       dif++;
//       comp2 = startEndPairs[ind+dif];
//     }
//     if (dif + ind >= 8192) {
//       ptr = 0x0;
//       break;
//     }
//     if ((comp2 - comp1) > size) {
//       ptr = (char*)comp1+1;
//       int plannedPos = ind+1;
//       if (startEndPairs[plannedPos] != 0x0) {
//         int tmpa = startEndPairs[plannedPos];
//         int tmpb = startEndPairs[plannedPos+1];
//
//         for (int i = plannedPos+2; i <= 8190; i++) {
//           int tmpc = tmpa;
//           tmpa = tmpb;
//           tmpb = startEndPairs[i];
//           startEndPairs[i] = tmpc;
//         }
//       } else {
//         startEndPairs[plannedPos] = (int) ptr;
//         startEndPairs[plannedPos+1] = (int) ptr + size;
//       }
//
//       break;
//     } else {
//       ind+=(dif+1);
//       dif = 1;
//     }
//   }
//
//   return ptr;
// }

void * operator new(size_t size) { return malloc(size); }

void * operator new[](size_t size) { return malloc(size); }

void operator delete(void *p) { free(p); }

void operator delete[](void *p) { free(p); }
