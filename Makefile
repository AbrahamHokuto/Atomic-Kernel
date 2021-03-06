vpath %.c core
vpath %.s core
CC=gcc
CXX=g++
LD=ld
AS=nasm
ASFLAGS=-felf
LDFLAGS=-T linker.ld -m elf_i386
SOURCES=kernel.o loader.o algorithm.o videodriver.o gdt_idt.o interrupts.o descriptor_tables.o isr.o timer.o keyboard.o assembly.o kheap.o paging.o string.o
CFLAGS=-Iinclude -m32 -Wall -Wextra -nostdlib -fno-builtin\
 -nostartfiles -nodefaultlibs -std=gnu99

rebuild:
	make clean
	make all

all:$(SOURCES)
	$(LD) $(LDFLAGS) -o kernel $(SOURCES)
clean:
	rm -rf *.o
	find ./ -name '*~' -exec rm {} \;

