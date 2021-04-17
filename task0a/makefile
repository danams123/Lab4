all: ass

ass: lab4_start.o lab4_util.o lab4_main.o
	ld -m elf_i386 lab4_start.o lab4_main.o lab4_util.o -o task0

lab4_start.o: lab4_start.s
	nasm -f elf32 lab4_start.s -o lab4_start.o

lab4_util.o: lab4_util.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector lab4_util.c -o lab4_util.o

lab4_main.o: lab4_main.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector lab4_main.c -o lab4_main.o

.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o task0