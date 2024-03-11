# Licensed under GPLv3
# Author    : Arka Mondal
# Date      : 14th July, 2023
# Copyright (C) 2024  Arka Mondal

ISODIR := isodir
SRCDIR := src
ISONAME := newbix.iso
BINNAME := newbix.bin

$(ISONAME) : $(ISODIR)/boot/$(BINNAME) $(ISODIR)/boot/grub/grub.cfg
	grub2-mkrescue -o $(ISONAME) $(ISODIR)

$(ISODIR)/boot/$(BINNAME) : $(SRCDIR)/$(BINNAME)
	cp -v $< $(ISODIR)/boot

$(SRCDIR)/$(BINNAME) :
	$(MAKE) -C $(SRCDIR)

.PHONY : buildbin
buildbin :
	$(MAKE) -C $(SRCDIR)

.PHONY : clean
clean :
	$(MAKE) -C $(SRCDIR) clean && rm -vf $(ISODIR)/boot/$(BINNAME) $(ISONAME)
