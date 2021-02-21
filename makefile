all : part1

part1 : part1.c
	gcc -pthread -o part1.out part1.c

clean :
	rm *.out
