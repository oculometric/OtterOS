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

void logInt(int i);
void logHex(int i);
void log(string s);

void sleep (int delay);

void fatal (string msg);
void warn (string msg);

bool shouldContinue = true;
// class Terminal {
// private:
// 	// Terminal constants
// 	static const size_t VGA_WIDTH;
// 	static const size_t VGA_HEIGHT;
//
// 	int terminal_row;
// 	int terminal_column;
// 	uint8_t terminal_color;
// 	uint16_t *terminal_buffer;
//
// 	char currentInLine[VGA_WIDTH];
// public:
//
// 	string getInLine ()
//
// 	void charTyped (char c)
//
// 	// Initialise the terminal mode
// 	void tInitialize();
//
// 	// Set the colour of the terminal
// 	void tSetCol(uint8_t color);
//
// 	// Put a character entry in a specific place
// 	void tPutEntryAt(char c, uint8_t color, size_t x, size_t y);
//
// 	// Move the cursor to the end of the text
// 	void updateCursorLocation();
//
// 	// Add a character to the end of the string
// 	void tPutChar(char c);
//
// 	// Delete the character at the cursor location
// 	void tDeleteChar();
//
// 	// Fill the current terminal line with a specific character
// 	void tFillLineWithChar(char c);
//
// 	// Write a string to the terminal
// 	void tWriteString(const char *data);
//
// 	// Print a string, then move to the next line
// 	void println(const char *data);
//
// 	// Print a string, but stay on the same line (if you don't go over anyway)
// 	void print(const char *data);
//
// 	// Clipboard data storage
// 	char clipboard[512];
//
// 	// Command history management
// 	char *inputHist[255];
// 	int histLoc;
// 	void updateInLineToHistory();
// };
