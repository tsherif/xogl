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

xogl.a: xogl.o xogl-context.o
	ar cr build/xogl.a build/xogl.o build/xogl-context.o && rm -f build/*.o

examples: triangle phong-cube

examples/build:
	mkdir examples/build

build:
	mkdir build

xogl-context.o: build
	$(CC) $(CFLAGS) -o build/$@ -c src/$*.c

xogl.o: build
	$(CC) $(CFLAGS) -o build/$@ -c src/$*.c

utils.o: examples/build
	$(CC) $(CFLAGS) -o examples/build/$@ -c examples/utils/$*.c

math.o: examples/build
	$(CC) $(CFLAGS) -o examples/build/$@ -c examples/utils/$*.c

triangle: xogl.a utils.o examples/build
	$(CC) $(CFLAGS) -o examples/build/$@ examples/$@.c build/xogl.a examples/build/utils.o $(LDLIBS)

phong-cube: xogl.a math.o utils.o examples/build
	$(CC) $(CFLAGS) -o examples/build/$@ examples/$@.c build/xogl.a examples/build/utils.o examples/build/math.o $(LDLIBS)


