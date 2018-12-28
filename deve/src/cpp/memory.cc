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
  int c = len;
  while (c--) {
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

typedef struct heap_block {
    size_t size;
    bool isFree;
    void *x;
} header;

unsigned char *usableStart = (unsigned char *) 0x0000000100000000;
heap_block *headers = (heap_block *) 0x00007E00;
int numHeaderBlocks = 0;

size_t allocatedSpace = 0;
size_t freeSpace = 0;

long long int heapSpace = 4294967296/2;

void prepMemory () {
  //memset ((char *)headers, '\0', 0x0007FFFF - (int)headers);
  heap_block b = heap_block ();
  b.size = heapSpace;
  b.isFree = true;
  b.x = usableStart;
  headers[0] = b;
  numHeaderBlocks++;
  freeSpace = heapSpace;
  //memset((char *)usableStart, 0x00000000, usableEnd-usableStart);
  // memset((char *)usableStart, 0xCCCCCCCC);
  // memset((char *)usableEnd,   0xCCCCCCCD);
}

void * malloc (size_t size) {
  if (size == 0 || size > heapSpace) return 0x0;
  int i = 0;
  while (i < numHeaderBlocks) {
    if (headers[i].isFree) {
      if (headers[i].size >= size) {
        // Found a free block large enough
        void *returnValue = headers[i].x;
        headers[i].size = headers[i].size - size;
        headers[i].x += size;

        int x = numHeaderBlocks;
        while (x > i) {
          headers[x] = headers[x-1];
          x--;
        }

        heap_block b = heap_block ();
        b.size = size;
        b.isFree = false;
        b.x = returnValue;
        headers[i] = b;
        numHeaderBlocks++;

        freeSpace -= size;
        allocatedSpace += size;
        return returnValue;
      }
    }
    i++;
  }

  return 0x0;
}

void updateAllocationTable () {
  logAllocationTable();
  // Merge adjacent free blocks if possible

}

void logAllocationTable () {
  logLn ("Logging allocation table:");
  for (int i = 0; i < numHeaderBlocks; i++) {
    log ("Item "); logInt(i);
    log ("Memory Address="); logHex ((long int)headers[i].x);
    log ("Is Free="); logBool (headers[i].isFree);
    log ("Size="); logInt (headers[i].size);
    logLn ("");
  }
}

void free (void *p) {
  int i = 0;
  while (i < numHeaderBlocks) {
    if (headers[i].x == p) {
      headers[i].isFree = true;
      break;
    }
    i++;
  }
  updateAllocationTable();
}

void * calloc(size_t size) {
  void *ptr = malloc(size);
  memset((char *)ptr, 0x00000000, size);
	return ptr;
}

void * operator new(size_t size) { return malloc(size); }

void * operator new[](size_t size) { return malloc(size); }

void operator delete(void *p) { free(p); }

void operator delete[](void *p) { free(p); }
