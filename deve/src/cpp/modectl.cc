#include "declarations.h"

// TODO: GDT Setup
// TODO: Working mode switching

void switchToRealMode () {
	logLn ("Going into real mode...");
	asm (R"(idt_real:
		.word 0x3ff
		.int 0
		cli
		mov %cr0, %eax
		and 0x7ffffffe, %eax
		mov %eax, %cr0


		GoRMode:
		mov $0x8000, %sp
		mov $0, %ax
		mov %ax, %ds
		mov %ax, %es
		mov %ax, %fs
		mov %ax, %gs
		mov %ax, %ss
		lidt idt_real
		sti  )");
		logLn ("Done");
	}

static inline void protectedBad () {
	logLn ("Going back into protected...");
	asm (R"(cli
		#lgdt (gdtr)
		mov %cr0, %eax
		or 1, %al
		mov %eax, %cr0
		jmp PModeMain

		PModeMain:
		# load DS, ES, FS, GS, SS, ESP)");
	logLn ("Done");
}

// Switch into real mode (not working)
static inline void changeToRealMode() {
  asm(R"(idt_real:
					.word 0x3ff
					.int 0
				savcr0:
      		.int 0
				Entry16:
					cli
					mov DATASEL16, %eax
					mov %eax, %ds
      		mov %eax, %es
      		mov %eax, %fs
      		mov %eax, %gs
      		mov %eax, %ss

      		mov %cr0, %eax
      		mov %eax, (savcr0)
      		and $0x7FFFFFFe, %eax
      		mov %eax, %cr0

      		jmp GoRMode

      	GoRMode:
      		mov $0x8000, %sp
      		mov $0, %ax
      		mov %ax, %ds
      		mov %ax, %es
      		mov %ax, %fs
      		mov %ax, %gs
      		mov %ax, %ss
      		lidt idt_real
      		sti
				)");
				logLn ("WE DID IT OMG");
}

// Switch into protected mode (not working)
static inline void changeToProtectedMode() {
  asm("cli          \n\t"
      "lgdt gdtr  \n\t"
      "mov %eax, %cr0 \n\t"
      "or %al, $1     \n\t"
      "mov %cr0, %eax");
}
