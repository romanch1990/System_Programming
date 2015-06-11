CREATE = gcc -Wall -ansi -pedantic

permut:		permut.o part1.o part2.o part3.o enum.c macro.c
		$(CREATE) -g -o permut permut.o part1.o part2.o part3.o enum.c macro.c
	
permut.o:	permut.c permut.h
		$(CREATE) -c permut.c
		
part1.o:	part1.c permut.h
		$(CREATE) -c part1.c
		
part2.o:	part2.c permut.h
		$(CREATE) -c part2.c
		
part3.o:	part3.c enum.c macro.c permut.h
		$(CREATE) -c part3.c enum.c macro.c
		
enum.o:		enum.c permut.h
		$(CREATE) -c enum.c
		
macro.o:	macro.c permut.h
		$(CREATE) -c macro.c
