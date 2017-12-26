CFLAGS=-g -Wall
CC=gcc
LDLIBS=-lX11 -lGL -lm

out:
	mkdir out

linux-opengl.o: out
	$(CC) $(CFLAGS) -o out/$@ -c ../src/$*.c

logl-utils.o: 
	$(CC) $(CFLAGS) -o out/$@ -c utils/$*.c

logl-math.o: 
	$(CC) $(CFLAGS) -o out/$@ -c utils/$*.c

triangle: linux-opengl.o logl-utils.o
	$(CC) $(CFLAGS) -o out/$@ $@.c out/linux-opengl.o out/logl-utils.o $(LDLIBS)

phong-cube: linux-opengl.o logl-math.o logl-utils.o
	$(CC) $(CFLAGS) -o out/$@ $@.c out/linux-opengl.o out/logl-utils.o out/logl-math.o $(LDLIBS)


