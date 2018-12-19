/* # Mesh.cc #
 *
 * ## Description ##
 * The MESH interpreter code.
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
// TODO: Move this into a class
// Temporary storage, so we don't have to recompute things
char argumentString[512 * 7];
string splitLine[50];

const int length = 8;

const char* functionNames[length] = {"echo", "bell", "mesh", "clib",
                               "setv", "getv", "help", "exit"};
const char* functionDescriptions[length] = {
    "Prints whatever comes after the command.",
    "Sends the bell character. Still WIP.",
    "Displays information about the shell.",
    "Places data in the clipboard.",
    "Sets the value of an environment variable.",
    "Prints the value of an environment variable. Will soon be replaced with "
    "regex detectors.",
    "Displays command help.",
    "Terminates the kernel, causing immediate shutdown."};

void displayPrompt() {
	log ("Prompting the user for input...");
  t.tSetCol (make_color(COLOR_RED, COLOR_BLACK));
  t.moveToNextLine();
  t.print("cosh -> ");
	t.tSetCol (make_color(COLOR_GREEN, COLOR_BLACK));
	log ("Done");
}

// ========== BEGIN COMMAND FUNCTIONS ========== //

static void clib(Terminal t) { log ("Copying specified value to the clipboard..."); strcpy(argumentString, t.clipboard); log ("Done");}

static void setv(Terminal t) { log ("Calling setGlobal for specified name:value pair..."); setGlobal(splitLine[1], splitLine[2]); log ("Done");}

static void getv(Terminal t) { log ("Calling getGlobal for specified name..."); t.println(getGlobal(splitLine[1])); log ("Done");}

static void bell(Terminal t) { log ("Printing bell character..."); t.println("Ding!!!"); log ("Done");}

static void echo(Terminal t) { log ("Printing input..."); t.println(argumentString); log ("Done");}

static void mesh(Terminal t) {
	log ("Printing terminal data...");
  char* versionName = getGlobal("meshv");
  t.println("MESH - MEta SHell");
  t.print("Version: ");
  log(versionName);
  t.println(versionName);
  t.println("Created: 11/03/2018");
  t.println("Written: JavaxCosten");
  t.println("Designed: DaBatchMan and JavaxCosten");
  t.println("Copyright (C) 2018 SketchesJavax, DaBatchMan and tcassar");
	log ("Done");
}

static void help(Terminal t) {
	log ("Looping through commands to print funciton descriptions...");
  for (int i = 0; i < length; i++) {
    t.print(functionNames[i]);
    t.print(" - ");
    t.println(functionDescriptions[i]);
  }
	log ("Done");
}

static void exit(Terminal t) { log ("Terminating the kernel..."); shouldContinue = false; log ("Done");}

// ==========  END COMMAND FUNCTIONS  ========== //

// Index between commands and string equivalents
void (*functions[])(Terminal t) = {echo, bell, mesh, clib, setv, getv, help, exit};

// Interpret a line of input
void executeLine(Terminal t) {
	log ("Processing the current line of input...");
  // Temporary storage for the command part
  char *cmd = t.getInLine();

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
  splitStr(t.getInLine(), ' ', splitLine);

  // println (splitLine[0]);
  // println (splitLine[1]);
  // println (splitLine[2]);

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
    char *item = splitLine[o];
    for (int i = 0; item[i] != NULL; i++) {
      argumentString[argLoc] = item[i];
      argLoc++;
    }
    argumentString[argLoc] = ' ';
    argLoc++;
  }
	log ("Done");

	log ("Interpreting command...");
  // Interpret the command
  int contain = contains(functionNames, cmd);
  if (contain != -1) {
    // The command is in the index, we can run it
    functions[contain](t);
  } else {
    // The command wasn't in the index, we don't understand it
    // TODO: Add ability to search /bin/ directory for executables matching the
    // name given
    t.print("Unknown command: ");
    t.println(cmd);
  }
	log ("Done");
  // Update command log
  // inputHist[arraylen(inputHist)] = currentInLine;
  // histLoc = arraylen(inputHist)+1;
  // TODO: Set up command history

  // Reset and reprompt the user for input

  // Clear the input line
	log ("Resetting input line...");
  t.resetInLine();
	log ("Done");

  displayPrompt();
}
