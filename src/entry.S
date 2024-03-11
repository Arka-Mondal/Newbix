# entry.S    : complete the boot process, before jumping to kernel main
# Licensed under GPLv3
# Author    : Arka Mondal
# Date      : 18th May, 2023
# Copyright (C) 2024  Arka Mondal

#include "param.h"

# .set KSTACKSIZE, 4096
.set MULTIBOOT2_HEADER_MAGIC, 0xE85250D6
.set GRUB_MULTIBOOT_ARCHITECTURE_I386, 0
.set CHECKSUM, -(MULTIBOOT2_HEADER_MAGIC + GRUB_MULTIBOOT_ARCHITECTURE_I386 + (multiboot_header_end - multiboot_header))

.section .multiboot
.align 8
multiboot_header:
  # magic
  .long MULTIBOOT2_HEADER_MAGIC
  # isa : i386
  .long GRUB_MULTIBOOT_ARCHITECTURE_I386
  # header length
  .long multiboot_header_end - multiboot_header
  # checksum
  .long CHECKSUM

  # general tag structure
  # this marks the end of tag buffer space
  .short 0    # type
  .short 0    # flags
  .long 8     # size

multiboot_header_end:

.bss
.align 16
.comm stack, KSTACKSIZE

.data

.text
.global _start
.type _start, @function
_start:
  movl        $(stack + KSTACKSIZE), %esp

  # %eax contains the magic number
  pushl       %ebx
  # %ebx contains the pointer to the multiboot information structure
  pushl       %eax
  # call kmain() function to start kernel initialization
  call        kmain

  # clear interrupts and loops indefinitely if we ever return
  # from kmain()
  cli
loophere:
  hlt
  jmp         loophere

.size _start, .-_start
