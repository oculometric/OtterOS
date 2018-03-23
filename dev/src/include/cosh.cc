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
string* splitLine;

// Split command from arguments
void splitCommandAndArgs (char** returner) {
	int n;
	println (currentInLine);
	// Set the return list's first item to the command, character by character
	for (n = 0; n < 4; n++) {
		returner[0][n] = currentInLine[n];
		tPutChar (currentInLine[n]);
		tPutChar (returner[0][n]);
	}
	println (returner[0]);
	// Set the return list's second item to the remainder, character by character
	for (n = 4; currentInLine[n] != NULL; n++) {
		returner[1][n-4] = currentInLine[n];
	}
}

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
	//setGlobal (splitLine[1], splitLine[2]);
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
	string tmp[2] = {new char[512], new char[512]};

	// Split the input into its constituent parts
	splitCommandAndArgs (tmp);

	// Set the command part of the input to the value got by the splitter, etc
	cmd = tmp[0];
	argumentString = tmp[1];

	// TODO: Fix the string splitting algorithm

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
