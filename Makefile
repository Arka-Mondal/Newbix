# Licensed under GPLv3
# Author    : Arka Mondal
# Date      : 14th July, 2023
# Copyright (C) 2023  Arka Mondal

ISODIR := isodir
BUILDDIR := builddir
ISONAME := newbix.iso

CC := gcc
ARCH32FLAG := -m32
DILECTFLAG := -ffreestanding
CCFLAG := -Wall -Wextra
LDFLAG := -z noexecstack
LDPAGESIZE := -z max-page-size=4096
CLIBOBJECTS = $(BUILDDIR)/stdio.o $(BUILDDIR)/string.o
OBJECTS = $(BUILDDIR)/boot.o $(BUILDDIR)/gdtload.o $(BUILDDIR)/gdt.o \
					$(BUILDDIR)/idtload.o $(BUILDDIR)/idt.o $(BUILDDIR)/kernel.o $(BUILDDIR)/tty.o \
					$(BUILDDIR)/acpi.o $(BUILDDIR)/apic.o $(BUILDDIR)/stdio.o $(BUILDDIR)/string.o

# ------------------------------------------------------------------------

$(ISONAME) : $(ISODIR)/boot/newbix.bin $(ISODIR)/boot/grub/grub.cfg
	grub2-mkrescue -o $(ISONAME) $(ISODIR)

$(ISODIR)/boot/newbix.bin : $(BUILDDIR)/newbix.bin
	cp -v $< $(ISODIR)/boot

# ------------------------------------------------------------------------

$(BUILDDIR)/newbix.bin : $(OBJECTS) kernel.ld
	$(CC) -o $@ $(OBJECTS) -T kernel.ld $(ARCH32FLAG) $(DILECTFLAG) -nostdlib -lgcc $(LDFLAG) $(LDPAGESIZE)

$(BUILDDIR)/boot.o : boot/boot.s
	$(CC) -o $@ -c $< $(ARCH32FLAG)

$(BUILDDIR)/gdtload.o : init/gdtload.s
	$(CC) -o $@ -c $< $(ARCH32FLAG)

$(BUILDDIR)/gdt.o : init/gdt.c include/gdt.h
	$(CC) -o $@ -c $< $(ARCH32FLAG) $(DILECTFLAG) $(CCFLAG)

$(BUILDDIR)/idtload.o : init/idtload.s
	$(CC) -o $@ -c $< $(ARCH32FLAG)

$(BUILDDIR)/idt.o : init/idt.c include/idt.h
	$(CC) -o $@ -c $< $(ARCH32FLAG) $(DILECTFLAG) $(CCFLAG)

$(BUILDDIR)/acpi.o : init/acpi.c include/acpi.h include/string.h
	$(CC) -o $@ -c $< $(ARCH32FLAG) $(DILECTFLAG) $(CCFLAG)

$(BUILDDIR)/apic.o : init/apic.c include/apic.h include/stdio.h
	$(CC) -o $@ -c $< $(ARCH32FLAG) $(DILECTFLAG) $(CCFLAG)

$(BUILDDIR)/tty.o : tty/tty.c include/tty.h include/string.h
	$(CC) -o $@ -c $< $(ARCH32FLAG) $(DILECTFLAG) $(CCFLAG)

$(BUILDDIR)/kernel.o : kernel/kernel.c include/gdt.h include/idt.h \
											 include/tty.h include/acpi.h include/apic.h \
											 include/stdio.h
	$(CC) -o $@ -c $< $(ARCH32FLAG) $(DILECTFLAG) $(CCFLAG)

$(BUILDDIR)/stdio.o : lib/stdio.c include/stdio.h
	$(CC) -o $@ -c $< $(ARCH32FLAG) $(DILECTFLAG) $(CCFLAG)

$(BUILDDIR)/string.o : lib/string.c include/string.h
	$(CC) -o $@ -c $< $(ARCH32FLAG) $(DILECTFLAG) $(CCFLAG)

# ------------------------------------------------------------------------

.PHONY : clean
clean :
	rm -vf $(BUILDDIR)/*.o $(BUILDDIR)/$(ISONAME)
