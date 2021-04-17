all: ass

ass: lab4_start.o lab4_util.o flame2.o
	ld -m elf_i386 lab4_start.o flame2.o lab4_util.o -o flame2

lab4_start.o: lab4_start.s
	nasm -f elf32 lab4_start.s -o lab4_start.o

lab4_util.o: lab4_util.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector lab4_util.c -o lab4_util.o

flame2.o: flame2.c
	gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector flame2.c -o flame2.o

.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o flame2