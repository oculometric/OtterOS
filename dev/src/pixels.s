.section .text
.global setPixel
.type setPixel, @function

setPixel:
	mov %ah, 0x0C
	mov %al, 0x13
	int $0x10

	mov %ah, 0x0C
	mov %bh, 0
	mov %dx, 5
	mov %cx, 5
	mov %al, 0100
	int $0x10
