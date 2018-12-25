#include "declarations.h"

void OtterKernel::prepare () {
  //realBad();
  //regs16_t regs;

  // switch to 320x200x256 graphics mode
  //regs.ax = 0x0013;
  //int32(0x10, &regs);

  // full screen with blue color (1)
  //memset((char *)0xA0000, 1, (320*200));
  //asm ("mov $0x00, %al");
  //log ("Mark 1");
  //sleep (100);
  //log ("Reading video mode...");
  //asm ("mov $0x0F, %ah");
  //log ("Mark 2");
  //asm ("int $0x10"); // This line is failing, we invariably jump awawy into 0x89734720
  //log ("Mark 3");
  //uint32_t al_value;
  //asm("" : "=al"(al_value));
  //logHex (al_value);
  //log ("We damn well did it!");
  //protectedBad();
  log ("Hanging...");
  while (true); // Hang here

}
