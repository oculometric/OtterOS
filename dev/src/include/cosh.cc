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

// ========== BEGIN COMMAND FUNCTIONS ========== //

static void clib () {
	int it;
	for (it = 0; splitLine[1][it] != NULL; it++) {
		clipboard[it] = splitLine[1][it];
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
	println (getNthItemOf(currentInLine, ' ', 1));
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

char* functionNames[5] = { "echo", "bell", "cosh", "clib", "modv"};
void (* functions [])() = { echo,   bell,   cosh,   clib,   modv};

void executeLine () {
	char* cmd = currentInLine;

	
	for (int n = 0; n < 50; n++) {
		splitLine[n] = (char*) malloc (sizeof(char*));
	}
	allocarr(splitLine, 512, 50);
	splitStr(currentInLine, ' ', splitLine);
	// for (int n = 0; n < 50; n++) {
	// 	println (splitLine[n]);
	// }
	cmd = splitLine[0];

	int contain = contains (functionNames, cmd);
	if (contain != -1) {
		functions[contain]();
	} else {
		print ("I don't what this means: ");
		println (cmd);
	}

	//inputHist[arraylen(inputHist)] = currentInLine;
	//histLoc = arraylen(inputHist)+1;
	terminal_color = make_color(COLOR_RED, COLOR_BLACK);
	print("cosh -> ");
	terminal_color = make_color(COLOR_GREEN, COLOR_BLACK);
	for (int ind=0; currentInLine[ind] != 0x00; ind++) {
		currentInLine[ind] = 0x00;
	}
	//delete cmd;
}
