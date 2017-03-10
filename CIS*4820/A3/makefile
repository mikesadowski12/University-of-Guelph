

INCLUDES = -F/System/Library/Frameworks -framework OpenGL -framework GLUT -lm

a1: a1.c graphics.c visible.c graphics.h
	gcc a1.c graphics.c visible.c -o a1 $(INCLUDES) 

clean:
	rm -f a1	