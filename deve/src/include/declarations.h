/* # Declarations.h #
 *
 * ## Description ##
 * Declares any functions (mostly logging etc)
 * for the program to be able to use.
 *
 * ## Info ##
 * Created 29/03/18
 * Format C++ header
 * Written by JavaxCosten
 *
 * ## Copyright ##
 * Copyright (C) 2018 OtterOS Project - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the LICENSE, found in the top level directory.
 */

// Define string type
typedef char *string;

// Header declarations for various print functions
void println(const char *data);
void print(const char *data);
void tPutChar(const char data);

void log(int i);
void log(string s);
