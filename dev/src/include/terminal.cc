

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* Hardware text mode color constants. */
enum vga_color {
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};



uint8_t make_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

uint16_t make_vgaentry(char c, uint8_t color) {
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

size_t strlen(const char* str) {
	size_t ret = 0;
	while ( str[ret] != 0 )
	ret++;
	return ret;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 24;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;


char currentInLine[VGA_WIDTH];
//size_t lnLoc = 0;

void tInitialize() {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
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

bool strEqual (const char* str1, const char* str2) {
	bool returner = true;
   int ptr = 0;
	while (str1[ptr]!=0x00 && str2[ptr]!=0x00) {
      if (str1[ptr]!=str2[ptr]) {
         returner = false;
      }
      ptr++;
   }
   if (!(str1[ptr]==0x00 && str2[ptr]==0x00)) {
      returner = false;
   }

	return returner;
}

static char** splitStr (char* string, char delim) {
	// Fix/write this
	char* returner[127];
	int loc = 0;
	int innerLoc = 0;
	for (int i = 0; string[i] != 0x00; i++) {
		char c = string[i];
		if (c != ' ') {
			returner[loc][innerLoc] = c;
			innerLoc++;
		} else {
			print ("a string was ");
			println (returner[loc]);
			innerLoc = 0;
			loc++;
		}
	}
	print ("the first string was ");
	println (returner[1]);
	return returner;
}

static char* getFirstCmdPart (char* in) {
	char* returner;
}

int contains (char** array, char* str) {
	for (int itemNo = 0; array[itemNo] != 0x00; itemNo++) {
		if (strEqual (array[itemNo], str)) {
			return itemNo;
		}
	}
	return -1;
}

int arraylen (char** array) {
	int ret = -1;
	for (int itemNo = 0; array[itemNo] != 0x00; itemNo++) {
		ret++;
	}
	return ret+1;
}

// ========== BEGIN COMMAND FUNCTIONS ========== //

static void echo () {
	println ("Echo......");
}

static void bell () {
	println ("Ding!!!");
}

// ==========  END COMMAND FUNCTIONS  ========== //

char* functionNames[2] = {"echo", "bell"};
void (* functions [])() = {echo, bell};

char* inputHist[255];
int histLoc = 0;

 void updateInLineToHistory () {
// 	int t = terminal_column;
// 	terminal_column = 8;
//	currentInLine = inputHist[histLoc];
// 	print(inputHist[histLoc]);
 }

void executeLine () {
	// char* cmd = getFirstCmdPart(currentInLine);

	char* cmd = currentInLine;
	int contain = contains (functionNames, currentInLine);
	if (contain != -1) {
		functions[contain]();
	} else {
		print ("I don't what this means: ");
		println (cmd);
	}
	inputHist[arraylen(inputHist)] = currentInLine;
	histLoc = arraylen(inputHist)+1;
	print("cosh -> ");
	for (int ind=0; currentInLine[ind] != 0x00; ind++) {
		currentInLine[ind] = 0x00;
	}
	//currentInLine[VGA_WIDTH];

}
