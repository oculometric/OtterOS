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
#include "include/declarations.h"
#include "include/time.cc"
#include "include/memory.cc"
#include "include/utils.cc"
#include "include/otterKernel.cc"
#include "include/usqwerty.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// The starting point of the high level kernel
extern "C" void kernel_main(void) {
	// Designed to init into terminal for now.
	log ("Preparing memory manager...");
	prepMemory();
	log ("Done");
	log ("Starting Otter kernel...");
	OtterKernel* ok = new OtterKernel ();
	log ("Finished");
	log ("=========TERMINATE=========");
	// graphicalKernel();
}
