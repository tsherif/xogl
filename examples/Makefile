CFLAGS=-g -Wall
CC=gcc
LDLIBS=-lX11 -lGL -lm

out:
	mkdir out

xogl.o: out
	$(CC) $(CFLAGS) -o out/$@ -c ../src/$*.c

utils.o: 
	$(CC) $(CFLAGS) -o out/$@ -c utils/$*.c

math.o: 
	$(CC) $(CFLAGS) -o out/$@ -c utils/$*.c

triangle: xogl.o utils.o
	$(CC) $(CFLAGS) -o out/$@ $@.c out/xogl.o out/utils.o $(LDLIBS)

phong-cube: xogl.o math.o utils.o
	$(CC) $(CFLAGS) -o out/$@ $@.c out/xogl.o out/utils.o out/math.o $(LDLIBS)


