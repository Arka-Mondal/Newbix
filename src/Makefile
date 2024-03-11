# Licensed under GPLv3
# Author    : Arka Mondal
# Date      : 11th March, 2024
# Copyright (C) 2024  Arka Mondal

BINNAME := newbix.bin
CLIBSRC := libc
INCLDIR := include

CC := gcc
ARCH32FLAG := -m32
DILECTFLAG := -ffreestanding
CCFLAG := -Wall -Wextra

LDFLAG := -z noexecstack
LDPAGESIZE := -z max-page-size=4096

CLIBOBJS = stdio.o string.o
OBJECTS = entry.o gdtload.o gdt.o idtload.o idt.o kernel.o tty.o acpi.o apic.o stdio.o string.o

$(BINNAME) : $(OBJECTS) $(CLIBOBJS) kernel.ld
	$(CC) -o $@ $(OBJECTS) -T kernel.ld $(ARCH32FLAG) $(DILECTFLAG) -nostdlib -lgcc $(LDFLAG) $(LDPAGESIZE)

entry.o : entry.S
	$(CC) -o $@ -c $< $(ARCH32FLAG) -I $(INCLDIR)

gdtload.o : gdtload.s
	$(CC) -o $@ -c $< $(ARCH32FLAG)

gdt.o : gdt.c include/gdt.h
	$(CC) -o $@ -c $< $(ARCH32FLAG) $(DILECTFLAG) $(CCFLAG) -I $(INCLDIR)

idtload.o : idtload.s
	$(CC) -o $@ -c $< $(ARCH32FLAG)

idt.o : idt.c include/idt.h
	$(CC) -o $@ -c $< $(ARCH32FLAG) $(DILECTFLAG) $(CCFLAG) -I $(INCLDIR)

acpi.o : acpi.c include/acpi.h
	$(CC) -o $@ -c $< $(ARCH32FLAG) $(DILECTFLAG) $(CCFLAG) -I $(INCLDIR)

apic.o : apic.c include/apic.h
	$(CC) -o $@ -c $< $(ARCH32FLAG) $(DILECTFLAG) $(CCFLAG) -I $(INCLDIR)

tty.o : tty.c include/tty.h
	$(CC) -o $@ -c $< $(ARCH32FLAG) $(DILECTFLAG) $(CCFLAG) -I $(INCLDIR)

kernel.o : kernel.c include/gdt.h include/idt.h include/tty.h include/acpi.h include/apic.h
	$(CC) -o $@ -c $< $(ARCH32FLAG) $(DILECTFLAG) $(CCFLAG) -I $(INCLDIR)

stdio.o : $(CLIBSRC)/stdio.c include/stdio.h
	$(CC) -o $@ -c $< $(ARCH32FLAG) $(DILECTFLAG) $(CCFLAG) -I $(INCLDIR)

string.o : $(CLIBSRC)/string.c include/string.h
	$(CC) -o $@ -c $< $(ARCH32FLAG) $(DILECTFLAG) $(CCFLAG) -I $(INCLDIR)

.PHONY : clean
clean :
	rm -vf $(OBJECTS) $(CLIBOBJS) $(BINNAME)
