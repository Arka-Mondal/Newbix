ARCH32FLAG = -m32
DILECTFLAG = -ffreestanding
CCFLAG = -Wall -Wextra
LDFLAG = -z noexecstack
OBJECTS = boot.o gdtload.o gdt.o idtload.o idt.o kernel.o
CC = gcc

newbix.bin: $(OBJECTS) kernel.ld
	$(CC) -o $@ $(OBJECTS) -T kernel.ld $(ARCH32FLAG) $(DILECTFLAG) -nostdlib -lgcc $(LDFLAG)

boot.o:	boot.s
	$(CC) -o $@ -c $< $(ARCH32FLAG)

gdtload.o: gdtload.s
	$(CC) -o $@ -c $< $(ARCH32FLAG)

gdt.o: gdt.c gdt.h
	$(CC) -o $@ -c $< $(ARCH32FLAG) $(DILECTFLAG) $(CCFLAG)

idtload.o: idtload.s
	$(CC) -o $@ -c $< $(ARCH32FLAG)

idt.o: idt.c idt.h
	$(CC) -o $@ -c $< $(ARCH32FLAG) $(DILECTFLAG) $(CCFLAG)

kernel.o: kernel.c
	$(CC) -o $@ -c $< $(ARCH32FLAG) $(DILECTFLAG) $(CCFLAG)

.PHONY : clean
clean:
	rm -vf $(OBJECTS) newbix.bin
