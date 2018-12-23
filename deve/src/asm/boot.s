/* # Boot.s #
 *
 * ## Description ##
 * Does the dirty setup for kernel.cc, then calls kernel_main.
 *
 * ## Info ##
 * Created 12/03/18
 * Format assembly source
 * Written by JavaxCosten
 *
 * ## Copyright ##
 * Copyright (C) 2018 OtterOS Project - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the LICENSE, found in the top level directory.
 */

/* Mulitboot header and Magic number */
.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

/* Declare start function */
.section .text
get_vesa_info:
	mov .data, %ax
	mov %ax, %es

	mov 0x4f00, %ax
	mov vbe_info_structure, %di
	int $0x10
	ret

idt_real:
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
	sti

.global _start
.type _start, @function
_start:
   /* Set up stack */
	mov $stack_top, %esp
 	/* Call the main kernel */
	call kernel_main
.size _start, . - _start

.section .data:
vbe_info_structure:
	.ascii "VBE2"
	.lcomm table_data 512-4
