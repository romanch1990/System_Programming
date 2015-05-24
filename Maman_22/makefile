set:	main.o set.o
	gcc -Wall -ansi -pedantic -g -o set main.o set.o
	
set.o:	set.c
	gcc -Wall -ansi -pedantic -g -c set.c
	
main.o:	main.c set.h
	gcc -Wall -ansi -pedantic -g -c main.c
