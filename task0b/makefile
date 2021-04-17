all: ass

ass: lab4_start.o lab4_util.o patch.o
	ld -m elf_i386 lab4_start.o patch.o lab4_util.o -o patch

lab4_start.o: lab4_start.s
	nasm -f elf32 lab4_start.s -o lab4_start.o

lab4_util.o: lab4_util.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector lab4_util.c -o lab4_util.o

patch.o: patch.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector patch.c -o patch.o

.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o patch