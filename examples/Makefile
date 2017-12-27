###################################################################################
# The MIT License (MIT)
#
# Copyright (c) 2017 Tarek Sherif
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
###################################################################################

CFLAGS=-g -Wall
CC=gcc
LDLIBS=-lX11 -lGL -lm

out:
	mkdir out

xogl-context.o: out
	$(CC) $(CFLAGS) -o out/$@ -c ../src/$*.c

xogl.o: out
	$(CC) $(CFLAGS) -o out/$@ -c ../src/$*.c

xogl.a: xogl.o xogl-context.o
	ar cr out/xogl.a out/xogl.o out/xogl-context.o

utils.o: 
	$(CC) $(CFLAGS) -o out/$@ -c utils/$*.c

math.o: 
	$(CC) $(CFLAGS) -o out/$@ -c utils/$*.c

triangle: xogl.a utils.o
	$(CC) $(CFLAGS) -o out/$@ $@.c out/xogl.a out/utils.o $(LDLIBS)

phong-cube: xogl.a math.o utils.o
	$(CC) $(CFLAGS) -o out/$@ $@.c out/xogl.a out/utils.o out/math.o $(LDLIBS)


