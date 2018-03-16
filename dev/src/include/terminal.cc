/* Copyright (C) 2018 JavaxCosten - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the LICENSE, found in the top level directory.
 */

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* Hardware text mode color constants. */


static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 24;

int terminal_row;
int terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;


char currentInLine[VGA_WIDTH];
//size_t lnLoc = 0;

void tInitialize() {
	terminal_row = 0;
	terminal_column = 0;
	//terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_color = make_color(COLOR_GREEN, COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for ( size_t y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
			//currentInLine[x] = ' ';
		}
	}
}

void tSetCol(uint8_t color) {
	terminal_color = color;
}

void tPutEntryAt(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void updateCursorLocation() {
	unsigned short cursorLoc = (terminal_row*VGA_WIDTH)+terminal_column;
	// cursor LOW port to vga INDEX register
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char)(cursorLoc));
	// cursor HIGH port to vga INDEX register
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char)((cursorLoc>>8)));
}

void tPutChar(char c) {
	tPutEntryAt(c, terminal_color, terminal_column, terminal_row);
	if ( ++terminal_column == VGA_WIDTH ) {
		terminal_column = 0;
		if ( ++terminal_row == VGA_HEIGHT ) {
			terminal_row = 0;
			tInitialize();
		}
	}

	updateCursorLocation();
}

void tDeleteChar () {
	if (terminal_column > 8) {
		terminal_column--;
	}
	tPutEntryAt(' ', terminal_color, terminal_column, terminal_row);
	currentInLine[terminal_column - 8] = 0x00;
	updateCursorLocation();
}

void tFillLineWithChar (char c) {
	terminal_column = 0;
	for (int i=0;i<VGA_WIDTH;i++) {
		tPutChar (c);
	}
}

void tWriteString(const char* data) {
	size_t datalen = strlen(data);
	for ( size_t i = 0; i < datalen; i++ )
	tPutChar(data[i]);
}

void println (const char* data) {
	tWriteString (data);
	terminal_column = 0;
	terminal_row++;
	updateCursorLocation();
}

void print (const char* data) {
	tWriteString (data);
	updateCursorLocation();
}

// static splitStr (char* string, char delim, char** into) {
// 	// Fix/write this
// 	char returner[VGA_WIDTH][255];
// 	int loc = 0;
// 	int innerLoc = 0;
// 	for (int i = 0; string[i] != 0x00; i++) {
// 		char c = string[i];
// 		if (c != delim) {
// 			returner[loc][innerLoc] = c;
// 			innerLoc++;
// 			//tPutChar(c);
// 		} else {
// 			print ("a string was ");
// 			println (returner[loc]);
// 			innerLoc = 0;
// 			loc++;
// 		}
// 	}
// 	print ("the first string was ");
// 	println (returner[0]);
// 	//return (char**)returner;
// }

void splitStr(const char* str, const char d, char** into) {
    if(str != NULL)
    {
        int n = 0;
        int c = 0;
        for(int i = 0; str[c] != '\0'; i++,c++) {
            into[n][i] = str[c];
            if(str[c] == d) {
                into[n][i] = '\0';
                i = -1;
                ++n;
            }
        }
    }
}


void allocarr(char** pointers, int bytes, int slots) {
    // int i = 0;
    // while(i <= slots) {
    //     pointers[i] = (char*)calloc(1, bytes);
    //     ++i;
    // }
}

static char* getFirstCmdPart (char* in) {
	char* returner;
}

// ========== BEGIN COMMAND FUNCTIONS ========== //

static void split () {
	//splitStr (currentInLine, ' ');
}

static void bell () {
	println ("Ding!!!");
}

static void echo () {
	println ("Ding!!!");
}

static void cosh () {
	char* versionName = getValueForKey ("coshv");
	println ("COSH - Combined OtterOS SHell");
	print ("Version: ");
	println (versionName);
	println ("Created: 11/03/2018");
	println ("Written: JavaxCosten");
	println ("Designed: DaBatchMan and JavaxCosten");
	println ("Copyright (C) 2018 SketchesJavax, DaBatchMan and tcassar");
}

// ==========  END COMMAND FUNCTIONS  ========== //

char* functionNames[4] = {"echo", "bell", "cosh", "split"};
void (* functions [])() = {echo, bell, cosh, split};

char* inputHist[255];
int histLoc = 0;

 void updateInLineToHistory () {
// 	int t = terminal_column;
// 	terminal_column = 8;
//	currentInLine = inputHist[histLoc];
// 	print(inputHist[histLoc]);
 }


void executeLine () {
	char* line = currentInLine;

	char** splitLine /* = (char**)malloc(50*sizeof(char*))*/;
	// allocarr(splitLine, 512, 50);
	splitStr(line, ' ', splitLine);


	char* cmd = splitLine[0];
	int contain = contains (functionNames, cmd);
	if (contain != -1) {
		functions[contain]();
	} else {
		print ("I don't what this means: ");
		println (cmd);
	}

	inputHist[arraylen(inputHist)] = currentInLine;
	histLoc = arraylen(inputHist)+1;
	terminal_color = make_color(COLOR_RED, COLOR_BLACK);
	print("cosh -> ");
	terminal_color = make_color(COLOR_GREEN, COLOR_BLACK);
	for (int ind=0; currentInLine[ind] != 0x00; ind++) {
		currentInLine[ind] = 0x00;
	}
	//currentInLine[VGA_WIDTH];

}
