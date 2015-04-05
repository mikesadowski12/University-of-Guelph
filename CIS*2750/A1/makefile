#NAME: Mike Sadowski
#DATE: January 18th, 2015
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS2750 A1
#------------------------------------------------------------------------------------------------------
#sources used to help create this file:
#	randu.org/tutorials/c/libraries.php
#	stackoverflow.com/questions/10803109/simple-makefile-for-compiling-a-shared-object-library-file
#	stackoverflow.com/questions/2286441/c-makefile-rcv-ranlib
#------------------------------------------------------------------------------------------------------
all: compile link
#------------------------------------------------------------------------------------------------------
test: link
	gcc -Wall test.c libpm.a -o test
#------------------------------------------------------------------------------------------------------
compile:
	mkdir objects
	gcc -c *.c -I include
	mv *.o ./objects
#------------------------------------------------------------------------------------------------------
link: compile
	ar rcs libpm.a ./objects/*.o
#------------------------------------------------------------------------------------------------------
clean:
	rm -rf ./objects ./test *.o libpm.a
#------------------------------------------------------------------------------------------------------
