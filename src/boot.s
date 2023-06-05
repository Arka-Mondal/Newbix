# boot.s    : complete the boot process, before jumping to kernel main
# Licensed under GPLv3
# Author    : Arka Mondal
# Date      : 18th May, 2023
# Copyright (C) 2023  Arka Mondal

.set ALIGN,     1 << 0
.set MEMINFO,   1 << 1
.set FLAGS,     ALIGN | MEMINFO
.set MAGIC,     0x1BADB002
.set CHECKSUM,  -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.data

.text
.global _start
.type _start, @function
_start:
  movl        $stack_top, %esp

  call        gdt_init
  call        idt_init
  call        kmain

  cli
loophere:
  hlt
  jmp         loophere

.size _start, .-_start
