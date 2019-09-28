all: task

task: main.o func.o
	gcc -m32 -o task main.o func.o
	
main.o: main.c
	gcc -c main.c -o main.o -std=c99 -m32

func.o: func.asm
	nasm -f elf32 -o func.o func.asm

clean:
	rm -f *.o *.exe