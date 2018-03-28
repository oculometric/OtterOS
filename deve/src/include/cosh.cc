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
char argumentString[512*7];
string splitLine[50];

const int length = 8;

char* functionNames[length] = { "echo", "bell", "cosh", "clib", "setv", "getv", "help", "exit"};
char* functionDescriptions[length] = {
	"Prints whatever comes after the command.",
	"Sends the bell character. Still WIP.",
	"Displays information about the shell.",
	"Places data in the clipboard.",
	"Sets the value of an environment variable.",
	"Prints the value of an environment variable. Will soon be replaced with regex detectors.",
	"Displays command help.",
  "Terminates the kernel, causing immediate shutdown."
};

void displayPrompt () {
	terminal_color = make_color(COLOR_RED, COLOR_BLACK);
	print("cosh -> ");
	terminal_color = make_color(COLOR_GREEN, COLOR_BLACK);
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

static void setv () {setGlobal (splitLine[1], splitLine[2]);}

static void getv () {println(getGlobal (splitLine[1]));}

static void bell () {println ("Ding!!!");}

static void echo () {println (argumentString);}

static void cosh () {
	char* versionName = getGlobal ("coshv");
	println ("COSH - Combined OtterOS SHell");
	print ("Version: ");
	log (versionName);
	println (versionName);
	println ("Created: 11/03/2018");
	println ("Written: JavaxCosten");
	println ("Designed: DaBatchMan and JavaxCosten");
	println ("Copyright (C) 2018 SketchesJavax, DaBatchMan and tcassar");
}

static void help () {
	for (int i = 0; i < length; i++) {
		print (functionNames[i]);
		print (" - ");
		println (functionDescriptions[i]);
	}
}

static void exit () {shouldContinue=false;}

// ==========  END COMMAND FUNCTIONS  ========== //

// Index between commands and string equivalents
void (* functions [])() = { echo,   bell,   cosh,   clib,   setv,   getv,   help, exit};


// Interpret a line of input
void executeLine () {
	// Temporary storage for the command part
	char* cmd = currentInLine;

	// Allocate an array to contain the input
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

	for (int o = 0; o < 8; o++) {
		for (int i = 0; i < 512; i++) {
			splitLine[o][i] = NULL;
		}
	}

	// Split the input into its constituent parts
	splitStr (currentInLine, ' ', splitLine);

	//println (splitLine[0]);
	//println (splitLine[1]);
	//println (splitLine[2]);

	// Zero the values of cmd and argumentString
	for (int i = 0; cmd[i] != NULL; i++) {
		cmd[i] = NULL;
	}

	for (int i = 0; argumentString[i] != NULL; i++) {
		argumentString[i] = NULL;
	}


	// Set the command part of the input to the value got by the splitter, etc
	cmd = splitLine[0];

	// Set the argument part of the input
	int argLoc = 0;
	for (int o = 1; o < 8; o++) {
		char* item = splitLine[o];
		for (int i = 0; item[i] != NULL; i++) {
			argumentString[argLoc] = item[i];
			argLoc++;
		}
		argumentString[argLoc] = ' ';
		argLoc++;
	}

	// Interpret the command
	int contain = contains (functionNames, cmd);
	if (contain != -1) {
		// The command is in the index, we can run it
		functions[contain]();
	} else {
		// The command wasn't in the index, we don't understand it
		// TODO: Add ability to search /bin/ directory for executables matching the name given
		print ("Unknown command: ");
		println (cmd);
	}

	// Update command log
	// inputHist[arraylen(inputHist)] = currentInLine;
	// histLoc = arraylen(inputHist)+1;
	// TODO: Set up command history/log

	// Reset and reprompt the user for input
	displayPrompt();
	// Clear the input line
	for (int ind=0; ind < VGA_WIDTH; ind++) {
		currentInLine[ind] = 0x00;
	}
}
