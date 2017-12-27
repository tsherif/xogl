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

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include "utils/utils.h"
#include "../src/xogl.h"

#define XK_LATIN1
#include <X11/keysymdef.h>

int main(int argc, char const *argv[]) {
    Display* disp;
    Window win;
    XEvent event;
    XWindowAttributes xWinAtt;

    GLuint angleLocation;

    // X Windows stuff
    disp = XOpenDisplay(NULL);

    if (disp == NULL) {
        printf("Unable to connect to X Server\n");
        return 1;
    }

    win = XCreateSimpleWindow(disp, DefaultRootWindow(disp), 20, 20, 2000, 2000, 0, 0, 0);
    

    XSelectInput(disp, win, ExposureMask | KeyPressMask | ButtonPressMask);
    XStoreName(disp, win, "Tarek's Bare-bones OpenGL App!");
    XMapWindow(disp, win);

    if (xogl_init(disp, win, 4, 5)) {
        fprintf(stderr, "Unable initialize OpenGL!\n");
        return 1;
    }

    glClearColor(0.0, 0.0, 0.0, 1.0);

    GLuint vertexArray = 0;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    GLfloat positionData[] = {
        -0.5, -0.5,
        0.5, -0.5,
        0.0, 0.5
    };

    GLuint positions = 0;
    glGenBuffers(1, &positions);
    glBindBuffer(GL_ARRAY_BUFFER, positions);
    glBufferData(GL_ARRAY_BUFFER, 3 * 2 * sizeof(GLfloat), positionData, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    GLubyte colorData[] = {
        255, 0, 0,
        0, 255, 0,
        0, 0, 255
    };

    GLuint colors = 0;
    glGenBuffers(1, &colors);
    glBindBuffer(GL_ARRAY_BUFFER, colors);
    glBufferData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(GLubyte), colorData, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, NULL);
    glEnableVertexAttribArray(1);

    const char* vsSource =
    "#version 450\n"
    "layout(location=0) in vec2 position;\n"
    "layout(location=1) in vec3 color;\n"
    "uniform float angle;\n"
    "out vec3 vColor;\n"
    "void main() {\n"
    "    vColor = color;\n"
    "    mat2 rotation = mat2(\n"
    "       sin(angle), -cos(angle),\n"
    "       cos(angle), sin(angle)\n"
    "    );"
    "    gl_Position = vec4(rotation * position, 0.0, 1.0);\n"
    "}\n";

    const char* fsSource =
    "#version 450\n"
    "in vec3 vColor;\n"
    "out vec4 fragColor;\n"
    "void main() {\n"
    "    fragColor = vec4(vColor, 1.0);\n"
    "}\n";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsSource, NULL);
    glCompileShader(vs);

    int params = -1;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &params);
    if (params != GL_TRUE) {
        printf("Vertex shader did not compile!\n");
        // char buffer[1024];
        // glGetShaderInfoLog(vs, 1024, 0, buffer);
        // printf("%s\n", buffer);
        exit(1);
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsSource, NULL);
    glCompileShader(fs);

    params = -1;
    glGetShaderiv(fs, GL_COMPILE_STATUS, &params);
    if (params != GL_TRUE) {
        printf("Fragment shader did not compile!\n");
        exit(1);
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    params = -1;
    glGetProgramiv(program, GL_LINK_STATUS, &params);

    if (params != GL_TRUE) {
        printf("Program did not link!\n");
        exit(1);
    }

    glUseProgram(program);

    angleLocation = glGetUniformLocation(program, "angle");

    float frameTime = 1000.0 / 60.0; 
    double startTime, endTime;

    // Animation loop
    while (1) {
        startTime = utils_getTime();    

        if (XCheckWindowEvent(disp, win, ExposureMask | KeyPressMask, &event) == True) {

            if (event.type == Expose) {
                XGetWindowAttributes(disp, win, &xWinAtt);
                glViewport(0, 0, xWinAtt.width, xWinAtt.height);
            }

            if (event.type == KeyPress) {
                KeySym key = XLookupKeysym(&event.xkey, 0);
                
                if (key == XK_q) {
                    break;
                }
            }
        }

        glUniform1f(angleLocation, startTime / 1000.0);

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        xogl_swapBuffers(disp, win);

        endTime = utils_getTime();
        double elapsed = endTime - startTime;
        if (elapsed < frameTime) {
            utils_milisleep(frameTime - elapsed);
            endTime = utils_getTime();
        }
    };

    // Teardown
    xogl_destroy(disp);
    XDestroyWindow(disp, win);
    XCloseDisplay(disp);
    printf("Done!\n");
}
