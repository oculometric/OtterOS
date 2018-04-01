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

 void* usableStart = (void*) 0xCDCDCDCD;
 void* usableEnd   = (void*) 0xFDFDFDFD;

 void* memset(void* b, int c, size_t len) {
     char* p = (char*)b;
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

 void malloc (int size) {
  
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
