/* # Cosh.cc #
 *
 * ## Description ##
 * The COSH interpreter code.
 *
 * ## Info ##
 * Created 22/03/18
 * Format C++ source
 * Written by JavaxCosten
 *
 * ## Copyright ##
 * Copyright (C) 2018 OtterOS Project - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the LICENSE, found in the top level directory.
 */

// Temporary storage, so we don't have to recompute things
string argumentString;
string splitLine[50];

// ========== BEGIN COMMAND FUNCTIONS ========== //

static void clib () {
	int it;
	for (it = 0; argumentString[it] != NULL; it++) {
		clipboard[it] = argumentString[it];
	}
	for (it=it;clipboard[it] != NULL; it++) {
		clipboard[it] = NULL;
	}
}

static void modv () {
	setGlobal (splitLine[1], splitLine[2]);
}

static void bell () {
	println ("Ding!!!");
}

static void echo () {
	println (argumentString);
}

static void cosh () {
	char* versionName = getGlobal ("coshv");
	println ("COSH - Combined OtterOS SHell");
	print ("Version: ");
	println (versionName);
	println ("Created: 11/03/2018");
	println ("Written: JavaxCosten");
	println ("Designed: DaBatchMan and JavaxCosten");
	println ("Copyright (C) 2018 SketchesJavax, DaBatchMan and tcassar");
}

// ==========  END COMMAND FUNCTIONS  ========== //

// Index between commands and string equivalents
char* functionNames[5] = { "echo", "bell", "cosh", "clib", "modv"};
void (* functions [])() = { echo,   bell,   cosh,   clib,   modv};

// Interpret a line of input
void executeLine () {
	// Temporary storage for the command part
	char* cmd = currentInLine;

	// Allocate an array to contain the input

	// Clear the memory we want
	// #define usable (void *)0xCDCDCDCD
	//
	// size_t len = 50 * 512;
	// memset (usable, 0x00, len);

	// char tmp[512];
	// for (int i = 0; i < 50; i++) {
	// 	//char t[512*i];
	// 	//char tmp[512];
	// 	//print ((char*)&tmp);
	// 	//char* a = ((char*) calloc (512*sizeof(char)));
	// 	// Set the value of splitline to
	// 	splitLine[i] = (string)((unsigned char*)usable + (i*512));
	//
	// }
	char a[512];
	char b[512];
	char c[512];
	char d[512];
	char e[512];
	char f[512];
	char g[512];
	char h[512];

	splitLine[0] = a;
	splitLine[1] = b;
	splitLine[2] = c;
	splitLine[3] = d;
	splitLine[4] = e;
	splitLine[5] = f;
	splitLine[6] = g;
	splitLine[7] = h;

	// Split the input into its constituent parts
	splitStr (currentInLine, ' ', splitLine);


	// Set the command part of the input to the value got by the splitter, etc
	cmd = splitLine[0];
	int argLoc = 0;
	for (int o = 1; o < 8; o++) {
		for (int i = 0; i < 512; i++) {
			argumentString[argLoc] = splitLine[o][i];
			argLoc++;
		}
		argumentString[argLoc] = ' ';
		argLoc++;
	}


	argumentString = splitLine[1];

	// Interpret the command
	int contain = contains (functionNames, cmd);
	if (contain != -1) {
		// The command is in the index, we can run it
		functions[contain]();
	} else {
		// The command wasn't in the index, we don't understand it
		// TODO: Add ability to search /bin/ directory for executables matching the name given
		print ("I don't know what this means: ");
		println (cmd);
	}

	// Update command log
	// inputHist[arraylen(inputHist)] = currentInLine;
	// histLoc = arraylen(inputHist)+1;
	// TODO: Set up command history/log

	// Reset and reprompt the user for input
	terminal_color = make_color(COLOR_RED, COLOR_BLACK);
	print("cosh -> ");
	terminal_color = make_color(COLOR_GREEN, COLOR_BLACK);

	// Clear the input line
	for (int ind=0; currentInLine[ind] != 0x00; ind++) {
		currentInLine[ind] = 0x00;
	}
}
