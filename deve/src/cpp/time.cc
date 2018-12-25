/* # Time.cc #
 *
 * ## Description ##
 * Functions for sleeping etc.
 *
 * ## Info ##
 * Created 16/04/18
 * Format C++ source
 * Written by JavaxCosten
 *
 * ## Copyright ##
 * Copyright (C) 2018 OtterOS Project - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the LICENSE, found in the top level directory.
 */

#include "declarations.h"

void sleep (int delay) {
	int del = delay * 10000000;
	volatile int sink;
    do {
        sink = 0;
    } while (--del > 0);
    (void)sink;
}
