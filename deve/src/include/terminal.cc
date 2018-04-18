/* # Terminal.cc #
*
* ## Description ##
* Functions for controlling the terminal mode operating
* system. Also contains command interpreter, and
* command functions. Includes string split function.
*
* ## Info ##
* Created 15/03/18
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

class Terminal {
private:

	int terminal_row;
	int terminal_column;
	uint8_t terminal_color;
	uint16_t *terminal_buffer;

	char currentInLine[VGA_WIDTH];
public:
	// Terminal constants
	static const size_t VGA_WIDTH = 80;
	static const size_t VGA_HEIGHT = 24;
	
	string getInLine () {
		return currentInLine;
	}

	void charTyped (char c) {
		currentInLine[terminal_column - 8] = c;
		tPutChar(c);
	}

	// Initialise the terminal mode
	void tInitialize() {
		terminal_row = 0;
		terminal_column = 0;
		terminal_color = make_color(COLOR_GREEN, COLOR_BLACK);
		terminal_buffer = (uint16_t *)0xB8000;
		for (size_t y = 0; y < VGA_HEIGHT; y++) {
			for (size_t x = 0; x < VGA_WIDTH; x++) {
				const size_t index = y * VGA_WIDTH + x;
				terminal_buffer[index] = make_vgaentry(' ', terminal_color);
			}
		}
	}

	// Set the colour of the terminal
	void tSetCol(uint8_t color) { terminal_color = color; }

	// Put a character entry in a specific place
	void tPutEntryAt(char c, uint8_t color, size_t x, size_t y) {
		const size_t index = y * VGA_WIDTH + x;
		terminal_buffer[index] = make_vgaentry(c, color);
	}

	// Move the cursor to the end of the text
	void updateCursorLocation() {
		unsigned short cursorLoc = (terminal_row * VGA_WIDTH) + terminal_column;
		// cursor LOW port to vga INDEX register
		outb(0x3D4, 0x0F);
		outb(0x3D5, (unsigned char)(cursorLoc));
		// cursor HIGH port to vga INDEX register
		outb(0x3D4, 0x0E);
		outb(0x3D5, (unsigned char)((cursorLoc >> 8)));
	}

	// Add a character to the end of the string
	void tPutChar(char c) {
		tPutEntryAt(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT) {
				terminal_row = 0;
				tInitialize();
			}
		}

		updateCursorLocation();
	}

	// Delete the character at the cursor location
	void tDeleteChar() {
		if (terminal_column > 8) {
			terminal_column--;
		}
		tPutEntryAt(' ', terminal_color, terminal_column, terminal_row);
		currentInLine[terminal_column - 8] = 0x00;
		updateCursorLocation();
	}

	// Fill the current terminal line with a specific character
	void tFillLineWithChar(char c) {
		terminal_column = 0;
		for (int i = 0; i < VGA_WIDTH; i++) {
			tPutChar(c);
		}
	}

	// Write a string to the terminal
	void tWriteString(const char *data) {
		size_t datalen = strlen(data);
		for (size_t i = 0; i < datalen; i++)
		tPutChar(data[i]);
	}

	// Print a string, then move to the next line
	void println(const char *data) {
		tWriteString(data);
		terminal_column = 0;
		if (terminal_row < VGA_HEIGHT) {
			terminal_row++;
		} else {
			tInitialize();
		}
		updateCursorLocation();
	}

	// Print a string, but stay on the same line (if you don't go over anyway)
	void print(const char *data) {
		tWriteString(data);
		updateCursorLocation();
	}

	// Clipboard data storage
	char clipboard[512];

	// Command history management
	char *inputHist[255];
	int histLoc = 0;

	// Updates the history according to which part of it you have selected
	// TODO: Fix history management
	void updateInLineToHistory() {
		// int t = terminal_column;
		// terminal_column = 8;
		// currentInLine = inputHist[histLoc];
		// print(inputHist[histLoc]);
	}
};
