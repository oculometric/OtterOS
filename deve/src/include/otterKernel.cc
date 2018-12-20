#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

class OtterKernel {
public:
  void prepare () {
    realBad();
    //regs16_t regs;

    // switch to 320x200x256 graphics mode
    //regs.ax = 0x0013;
    //int32(0x10, &regs);

    // full screen with blue color (1)
    log ("Trying to set");
    //memset((char *)0xA0000, 1, (320*200));
    //asm ("mov $0x00, %al");
    //log ("Mark 1");
    log ("Reading video mode...");
    asm ("mov $0x0F, %ah");
    log ("Mark 2");
    asm ("# is this working?");
    asm ("int $0x10");
    uint32_t al_value;
    asm("" : "=al"(al_value));
    logHex (al_value);
    log ("We damn well did it!");
    protectedBad();
    while (true);

  }

private:

};
