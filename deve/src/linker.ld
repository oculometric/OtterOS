/* Copyright (C) 2018 JavaxCosten - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the LICENSE, found in the top level directory.
 */

ENTRY(_start)

SECTIONS {
  .= 1M;

  /* First put the multiboot header */
  .text BLOCK(4K)
      : ALIGN(4K){*(.multiboot) * (.text)}

            /* Read-only data. */
            .rodata
            BLOCK(4K)
      : ALIGN(4K){*(.rodata)}

            /* Read-write data (initialized) */
            .data
            BLOCK(4K)
      : ALIGN(4K){*(.data)}

            /* Read-write data (uninitialized) and stack */
            .bss
            BLOCK(4K)
      : ALIGN(4K) {
    *(COMMON) * (.bss)
  }
}
