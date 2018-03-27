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
.global _start
.type _start, @function
_start:
   /* Set up stack */
	mov $stack_top, %esp
 	/* Call the main kernel */
	call kernel_main
.size _start, . - _start