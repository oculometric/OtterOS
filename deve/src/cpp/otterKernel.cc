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
  Terminal *t = new Terminal ();
  t->setActiveStyleFlag (t->make_color(vga_color::COLOR_RED, vga_color::COLOR_WHITE));
  t->resetTerminal();
  while (true) {
    t->println ("Hi there!");
    t->println ("It be working my doods.");
    t->println ("We're gonna stay right here...");
    sleep (60);
    t->println ("Screw this!");
    sleep (30);
    t->deleteLines (2);
    t->setActiveStyleFlag(t->make_color(vga_color::COLOR_CYAN, vga_color::COLOR_MAGENTA));
    t->println ("Let's do it again!");
    t->setActiveStyleFlag (t->make_color(vga_color::COLOR_RED, vga_color::COLOR_WHITE));
    sleep (30);
  }
}
