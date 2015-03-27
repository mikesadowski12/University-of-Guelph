
# Flags that are sent to the compiler
# Do not change these
CFLAGS      =	-Wall -ansi -pedantic -g -Iinclude


music:
	gcc $(CFLAGS) src/main.c src/linkedList.c src/musicFile.c -o bin/a4

test: 
	gcc $(CFLAGS) src/listTest.c src/linkedList.c -o bin/listTest

clean:
	@ rm *.o
