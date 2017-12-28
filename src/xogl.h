///////////////////////////////////////////////////////////////////////////////////
// The MIT License (MIT)
//
// Copyright (c) 2017 Tarek Sherif
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
///////////////////////////////////////////////////////////////////////////////////

/** 
    @file
*/

#ifndef _XOGL_H_
#define _XOGL_H_

#include "glcore.h"

/**
    @brief Initialize OpenGL context for given window and load OpenGL functions.
    @param disp Open X11 display connection.
    @param win X11 window to get the OpenGL context from.
    @param major OpenGL major version number.
    @param minor OpenGL minor version number.
*/
int xogl_init(Display* disp, Window win, int major, int minor);

/**
    @brief Swap the back and front default framebuffers. Call after
        completing the GL calls for a frame.
*/
void xogl_swapBuffers(void);

/**
    @brief Destroy the OpenGL context.
    @param disp Open X11 display connection.
*/
void xogl_destroy(void);

#endif
