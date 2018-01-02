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

///////////////////////////////////////////////////////////////
//  Compute example from: http://wili.cc/blog/opengl-cs.html
///////////////////////////////////////////////////////////////

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

    // X Windows stuff
    disp = XOpenDisplay(NULL);

    if (disp == NULL) {
        printf("Unable to connect to X Server\n");
        return 1;
    }

    win = XCreateSimpleWindow(disp, DefaultRootWindow(disp), 20, 20, 2000, 2000, 0, 0, 0);
    

    XSelectInput(disp, win, ExposureMask | KeyPressMask | ButtonPressMask);
    XStoreName(disp, win, "XOGL Compute Example");
    XMapWindow(disp, win);

    if (xogl_init(disp, win, 4, 5)) {
        fprintf(stderr, "Unable initialize OpenGL!\n");
        return 1;
    }

    glClearColor(0.0, 0.0, 0.0, 1.0);

    GLuint vertexArray = 0;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    GLuint positions = 0;
    glGenBuffers(1, &positions);
    glBindBuffer(GL_ARRAY_BUFFER, positions);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QUAD_POSITIONS), QUAD_POSITIONS, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);



    const char* vsSource =
    "#version 450\n"
    "layout(location=0) in vec2 position;\n"
    "out vec2 vUV;\n"
    "void main() {\n"
    "    vUV = position * 0.5 + 0.5;\n"
    "    gl_Position = vec4(position, 0.0, 1.0);\n"
    "}\n";

    const char* fsSource =
    "#version 450\n"
    "in vec2 vUV;\n"
    "layout(binding=0) uniform sampler2D tex;\n"
    "out vec4 fragColor;\n"
    "void main() {\n"
    "    fragColor = vec4(texture(tex, vUV).r, 1.0, 1.0, 1.0);\n"
    "}\n";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsSource, NULL);
    glCompileShader(vs);

    int params = -1;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &params);
    if (params != GL_TRUE) {
        printf("Vertex shader did not compile!\n");
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

    const char* csSource =
    "#version 450\n"
    "uniform float roll;\n"
    "layout(r8, binding=0) uniform image2D result;\n"
    "layout(local_size_x=16, local_size_y=16) in;\n"
    "void main() {\n"
    "    ivec2 index = ivec2(gl_GlobalInvocationID.xy);\n"
    "    float local = length(vec2(ivec2(gl_LocalInvocationID.xy) - 8) / 8.0);\n"
    "    float global = sin(float(gl_WorkGroupID.x + gl_WorkGroupID.y) * 0.1 + roll) * 0.5;\n"
    "    imageStore(result, index, vec4(1.0 - global * local, 0.0, 0.0, 0.0));\n"
    "}\n";

    GLuint cs = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(cs, 1, &csSource, NULL);
    glCompileShader(cs);

    params = -1;
    glGetShaderiv(cs, GL_COMPILE_STATUS, &params);
    if (params != GL_TRUE) {
        char buffer[1024];
        glGetShaderInfoLog(cs, 1024, NULL, buffer);
        printf("Compute shader did not compile! %s\n", buffer);
        exit(1);
    }

    GLuint computeProgram = glCreateProgram();
    glAttachShader(computeProgram, cs);
    glLinkProgram(computeProgram);

    params = -1;
    glGetProgramiv(computeProgram, GL_LINK_STATUS, &params);

    if (params != GL_TRUE) {
        printf("Program did not link!\n");
        exit(1);
    }

    GLuint rollLocation = glGetUniformLocation(computeProgram, "roll");

    GLuint tex = 0;
    glGenTextures(1, &tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, NULL);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glBindImageTexture(0, tex, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R8);

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

        glUseProgram(computeProgram);
        glUniform1f(rollLocation, -startTime * 0.001f);
        glDispatchCompute(512 / 16, 512 / 16, 1);

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        xogl_swapBuffers();

        endTime = utils_getTime();
        double elapsed = endTime - startTime;
        if (elapsed < frameTime) {
            utils_milisleep(frameTime - elapsed);
            endTime = utils_getTime();
        }
    };

    // Teardown
    xogl_destroy();
    XDestroyWindow(disp, win);
    XCloseDisplay(disp);
    printf("Done!\n");
}
