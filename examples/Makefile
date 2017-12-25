CFLAGS=-g -Wall
CC=gcc
LDLIBS=-lX11 -lGL -lm

out:
	mkdir out

linux-opengl.o: out
	$(CC) $(CFLAGS) -o out/$@ -c ../src/$*.c

mat4.o: 
	$(CC) $(CFLAGS) -o out/$@ -c math/$*.c

vec3.o:
	$(CC) $(CFLAGS) -o out/$@ -c math/$*.c

triangle: linux-opengl.o
	$(CC) $(CFLAGS) -o out/$@ $@.c out/linux-opengl.o $(LDLIBS)

phong-cube: linux-opengl.o vec3.o mat4.o
	$(CC) $(CFLAGS) -o out/$@ $@.c out/linux-opengl.o out/vec3.o out/mat4.o $(LDLIBS)


