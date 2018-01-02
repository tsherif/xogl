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

build/xogl.a: build/xogl.o build/xogl-context.o
	ar cr build/xogl.a build/xogl.o build/xogl-context.o

examples: examples/build/triangle examples/build/phong-cube examples/build/dof examples/build/compute

examples/build:
	mkdir examples/build

build:
	mkdir build

build/xogl-context.o: | build
	$(CC) $(CFLAGS) -o build/xogl-context.o -c src/xogl-context.c

build/xogl.o: | build
	$(CC) $(CFLAGS) -o build/xogl.o -c src/xogl.c

examples/build/utils.o: | examples/build
	$(CC) $(CFLAGS) -o examples/build/utils.o -c examples/utils/utils.c

examples/build/math.o: | examples/build
	$(CC) $(CFLAGS) -o examples/build/math.o -c examples/utils/math.c

examples/build/triangle: examples/triangle.c build/xogl.a examples/build/utils.o | examples/build
	$(CC) $(CFLAGS) -o examples/build/triangle examples/triangle.c build/xogl.a examples/build/utils.o $(LDLIBS)

examples/build/phong-cube: examples/phong-cube.c build/xogl.a examples/build/math.o examples/build/utils.o | examples/build
	$(CC) $(CFLAGS) -o examples/build/phong-cube examples/phong-cube.c build/xogl.a examples/build/utils.o examples/build/math.o $(LDLIBS)

examples/build/dof: examples/dof.c build/xogl.a examples/build/math.o examples/build/utils.o | examples/build
	$(CC) $(CFLAGS) -o examples/build/dof examples/dof.c  build/xogl.a examples/build/utils.o examples/build/math.o $(LDLIBS)

examples/build/particles: examples/particles.c build/xogl.a examples/build/math.o examples/build/utils.o | examples/build
	$(CC) $(CFLAGS) -o examples/build/particles examples/particles.c build/xogl.a examples/build/utils.o examples/build/math.o $(LDLIBS)

examples/build/compute: examples/compute.c build/xogl.a examples/build/utils.o | examples/build
	$(CC) $(CFLAGS) -o examples/build/compute examples/compute.c build/xogl.a examples/build/utils.o $(LDLIBS)

clean:
	rm -rf build examples/build
