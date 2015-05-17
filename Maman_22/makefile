CREATE = gcc -Wall -ansi -pedantic -g

set:	main.o set.o
	$(CREATE) -o set main.o set.o
	
set.o:	set.c
	$(CREATE) -c set.c
	
main.o:	main.c set.h
	$(CREATE) -c main.c
