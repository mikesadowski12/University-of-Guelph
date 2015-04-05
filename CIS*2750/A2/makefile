#NAME: Mike Sadowski
#DATE: January 18th, 2015
#STUDENT ID: 0864810
#ASSIGNEMNT: CIS2750 A1
#------------------------------------------------------------------------------------------------------
#sources used to help create this file:
#	randu.org/tutorials/c/libraries.php
#	stackoverflow.com/questions/10803109/simple-makefile-for-compiling-a-shared-object-library-file
#	stackoverflow.com/questions/2286441/c-makefile-rcv-ranlib

# gcc -c -Wall PM_Converter.c -I/usr/lib/jvm/java-6-openjdk/include -I/usr/lib/jvm/java-6-openjdk/include/linux
# gcc -shared -fPIC -Wl,-soname,libPM_Converter.so -I/usr/lib/jvm/java-6-openjdk/include -I/usr/lib/jvm/java-6-openjdk/include/linux -o libPM_Converter.so PM_Converter.o
# export LD_LIBRARY_PATH={$LD_LIBRARY_PATH}:.
#------------------------------------------------------------------------------------------------------
all: compile link PM_Converter.o libPM_Converter.so PM_Converter.java Dialogc DialogcCompiler
#------------------------------------------------------------------------------------------------------
PM_Converter.o: PM_Converter.c cfiles/ParameterManager.h cfiles/ParameterManager.c
	gcc -c -Wall PM_Converter.c -I/usr/lib/jvm/java-6-openjdk/include -I/usr/lib/jvm/java-6-openjdk/include/linux
	
libPM_Converter.so: PM_Converter.c PM_Converter.h libpm.a
	gcc PM_Converter.c -fPIC -shared -Wl,-soname,libPM_Converter.so -I/usr/lib/jvm/java-6-openjdk/include -I/usr/lib/jvm/java-6-openjdk/include/linux -o libPM_Converter.so -L. -lpm
	export LD_LIBRARY_PATH={$LD_LIBRARY_PATH}:.	
#------------------------------------------------------------------------------------------------------	
test: link
	gcc -Wall test.c libpm.a -o test
#------------------------------------------------------------------------------------------------------
DialogcCompiler: DialogcCompiler.java PM_Converter.java
	javac DialogcCompiler.java
#------------------------------------------------------------------------------------------------------	
Dialogc: DialogcCompiler.java PM_Converter.java DialogcCompiler.java
	javac Dialogc.java
#------------------------------------------------------------------------------------------------------	
compile:
	mkdir objects
	gcc -c -fPIC ./cfiles/*.c -I include
	mv *.o ./objects
#------------------------------------------------------------------------------------------------------
link: compile
	ar rcs libpm.a ./objects/*.o
#------------------------------------------------------------------------------------------------------
clean:
	rm -rf ./objects ./class ./test *.o *.class libpm.a libPM_Converter.so
#------------------------------------------------------------------------------------------------------
