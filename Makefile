all: lsi


lex: yac
	lex -o lsi.lex.c lsi.lex 


yac:
	yacc -v -d -o lsi.yac.c lsi.yac



lsi.lex.o: lex
	gcc -g -c -Wall lsi.lex.c -o obj/lsi.lex.o

lsi.yac.o: yac
	gcc -g -c -Wall lsi.yac.c -o obj/lsi.yac.o

functions.o:
	gcc -g -c -Wall functions.c -o obj/functions.o

data_structs.o:
	gcc -g -c -Wall data_structs.c -o obj/data_structs.o


lsi: lsi.lex.o lsi.yac.o functions.o data_structs.o
	gcc obj/lsi.yac.o obj/lsi.lex.o obj/functions.o obj/data_structs.o -o bin/lsi -ll -lm
	gcc -g obj/lsi.yac.o obj/lsi.lex.o obj/functions.o obj/data_structs.o -o debug/lsi -ll -lm
	rm obj/*
