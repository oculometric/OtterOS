/* Copyright (C) 2018 JavaxCosten - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the LICENSE, found in the top level directory.
 */

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

.section .text
.global _start
.type _start, @function
_start:
	mov $stack_top, %esp
	;sti

	;mov %ah, 0x00
	;mov %al, 0x03
	;int $0x10

	;mov %ah, 0x0C
	;mov %al, 15
	;mov %cx, 100
	;mov %dx, 100
	;int $0x10
	call kernel_main

; 	cli
; 1:	hlt
; 	jmp 1b

.size _start, . - _start
