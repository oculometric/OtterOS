/* # Kernel.cc #
*
* ## Description ##
* The core code for OtterOS. Every other part of the project
* branches from this starting point.
*
* ## Info ##
* Created 14/03/18
* Format C++ source
* Written by JavaxCosten
*
* ## Copyright ##
* Copyright (C) 2018 OtterOS Project - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the LICENSE, found in the top level directory.
*/

// Include libraries and other files
#include "declarations.h"

// The starting point of the high level kernel
extern "C" void kernel_main(void) {
	// Designed to init into terminal for now.
	init_serial();
	logLn ("Preparing memory manager...");
	prepMemory();
	logLn ("Done");
	logLn ("Starting Otter kernel...");
	OtterKernel* ok = new OtterKernel ();
	ok->prepare();
	logLn ("Finished");
	logLn ("=========TERMINATE=========");
	// graphicalKernel();
}
