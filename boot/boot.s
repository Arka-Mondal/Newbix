# boot.s    : complete the boot process, before jumping to kernel main
# Licensed under GPLv3
# Author    : Arka Mondal
# Date      : 18th May, 2023
# Copyright (C) 2023  Arka Mondal

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

  .short 0
  .short 0
  .long 8

multiboot_header_end:

.bss
.align 16
stack_bottom:
.skip 8192
stack_top:

.data

.text
.global _start
.type _start, @function
_start:
  movl        $stack_top, %esp

  # %eax contains the magic number
  # %ebx contains the pointer to the multiboot information structure
  pushl       %ebx
  pushl       %eax
  call        kmain

  cli
loophere:
  hlt
  jmp         loophere

.size _start, .-_start
