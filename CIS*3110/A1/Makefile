all: msh
msh: mshell.o lex.yy.o
	gcc -o msh mshell.o lex.yy.o -lfl  
mshell.o: mshell.c
	gcc -Wall -g -c mshell.c
lex.yy.o: lex.yy.c
	gcc -Wall -g -c lex.yy.c
lex.yy.c: lex.c
	flex lex.c
clean:
	rm -f *.o
	rm -f lex.yy.c
	rm -f msh
	
