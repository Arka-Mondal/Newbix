ISODIR := isodir
SRCDIR := src
ISONAME := newbix.iso

$(ISONAME) : $(ISODIR)/boot/newbix.bin $(ISODIR)/boot/grub/grub.cfg
	grub2-mkrescue -o $(ISONAME) $(ISODIR)

$(ISODIR)/boot/newbix.bin : $(SRCDIR)/newbix.bin
	cp -v $< $(ISODIR)/boot

$(SRCDIR)/newbix.bin :
	cd $(SRCDIR) ; make

.PHONY : clean
clean :
	rm -vf $(ISODIR)/boot/newbix.bin $(ISONAME)
