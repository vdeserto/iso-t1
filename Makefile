main: main.o commands.o
	gcc -o main main.o commands.o -lm 
main.o: main.c commands.h
	gcc -c main.c -lm
commands.o: commands.c commands.h
	gcc -c commands.c -lm 
	
	