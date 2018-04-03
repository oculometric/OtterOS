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

int usableStart = 0xCDCDCDCD;
int usedBytes   = 0;
int usableEnd   = 0xFDFDFDFD;


void* memset(void* s, int c, size_t len) {
  char* p = (char*)s;
  for (size_t i = 0; i != len; ++i) {
    p[i] = c;
  }
  return b;
}

void* memset (void* b, int c) {
  char* p = (char*)b;
  p[0] = c;
  return b;
}

void memcpy (void* a, void* b, int length) {
  char* origin = (char*) a;
  char* destination = (char*) b;
  for (int i = 0; i < length; i++) {
    destination[i] = origin[i];
  }
}

void memcpy (void* a, void* b) {
  char* origin = (char*) a;
  char* destination = (char*) b;
  destination[0] = origin[0];
}

void strcpy (string a, string b) {
  int it;
	for (it = 0; a[it] != NULL; it++) {
		b[it] = a[it];
	}
	for (it=it;b[it] != NULL; it++) {
		b[it] = NULL;
	}
}

void malloc (int size) {
  void ptr = 0x00000000;
  if (((int) usableStart + usedBytes + size) < usableEnd) {
    ptr = usableStart[usedBytes];
    usedBytes += size
  } else {
    log ("Shit!!!!!");
    log("We ran out of memory.");
    log ("Aggggh!!!");
  }
  return ptr;
}

void calloc (int size) {
  void ptr = malloc (size);
  memset (ptr, 0x00000000, size);
}

void *operator new(size_t size) {
  return malloc(size);
}

void *operator new[](size_t size) {
  return malloc(size);
}

void operator delete(void *p) {
  free(p);
}

void operator delete[](void *p) {
  free(p);
}
