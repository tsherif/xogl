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
#include <time.h>
#include <X11/Xlib.h>
#include "utils/utils.h"
#include "../src/xogl.h"

#define XK_LATIN1
#include <X11/keysymdef.h>

#define NUM_PARTICLES 200000

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
    XStoreName(disp, win, "XOGL Particle Example");
    XMapWindow(disp, win);

    if (xogl_init(disp, win, 4, 5)) {
        fprintf(stderr, "Unable initialize OpenGL!\n");
        return 1;
    }

    srand(time(0));
 
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    float positionData[NUM_PARTICLES * 3];
    unsigned char colorData[NUM_PARTICLES * 3];

    for (int i = 0; i < NUM_PARTICLES; ++i) {
        int vec3i = i * 3;

        positionData[vec3i] = ((float) rand() / RAND_MAX) * 2 - 1;
        positionData[vec3i + 1] = ((float) rand() / RAND_MAX) * 2 - 1;
        positionData[vec3i + 2] = ((float) rand() / RAND_MAX) * 2 - 1;

        colorData[vec3i] = rand() % 255;
        colorData[vec3i + 1] = rand() % 255;
        colorData[vec3i + 2] = rand() % 255;
    }


    GLuint vertexArrayA = 0;
    glGenVertexArrays(1, &vertexArrayA);
    glBindVertexArray(vertexArrayA);

    GLuint positionsA = 0;
    glGenBuffers(1, &positionsA);
    glBindBuffer(GL_ARRAY_BUFFER, positionsA);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STREAM_COPY);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    GLuint velocitiesA = 0;
    glGenBuffers(1, &velocitiesA);
    glBindBuffer(GL_ARRAY_BUFFER, velocitiesA);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), NULL, GL_STREAM_COPY);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    GLuint colors = 0;
    glGenBuffers(1, &colors);
    glBindBuffer(GL_ARRAY_BUFFER, colors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, NULL);
    glEnableVertexAttribArray(2);

    // Transform feedback handles output
    GLuint transformFeedbackA = 0;
    glGenTransformFeedbacks(1, &transformFeedbackA);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, transformFeedbackA);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, positionsA);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, velocitiesA);

    GLuint vertexArrayB = 0;
    glGenVertexArrays(1, &vertexArrayB);
    glBindVertexArray(vertexArrayB);

    GLuint positionsB = 0;
    glGenBuffers(1, &positionsB);
    glBindBuffer(GL_ARRAY_BUFFER, positionsB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), NULL, GL_STREAM_COPY);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    GLuint velocitiesB = 0;
    glGenBuffers(1, &velocitiesB);
    glBindBuffer(GL_ARRAY_BUFFER, velocitiesB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), NULL, GL_STREAM_COPY);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, colors);
    glVertexAttribPointer(2, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, NULL);
    glEnableVertexAttribArray(2);

    GLuint transformFeedbackB = 0;
    glGenTransformFeedbacks(1, &transformFeedbackB);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, transformFeedbackB);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, positionsB);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, velocitiesB);

    const char* vsSource =
    "#version 450\n"

    "layout(std140) uniform;\n"

    "layout(location=0) in vec3 aPosition;\n"
    "layout(location=1) in vec3 aVelocity;\n"
    "layout(location=2) in vec3 aColor;\n"

    "uniform Mass {\n"
        "vec4 mass1Position;\n"
        "vec4 mass2Position;\n"
        "vec4 mass3Position;\n"
        "float mass1Factor;\n"
        "float mass2Factor;\n"
        "float mass3Factor;\n"
    "};\n"

    "out vec3 vPosition;\n"
    "out vec3 vVelocity;\n"
    "out vec3 vColor;\n"
    "void main() {\n"
        "vec3 position = aPosition;\n"
        "vec3 velocity = aVelocity;\n"

        "vec3 massVec = mass1Position.xyz - position;\n"
        "float massDist2 = max(0.01, dot(massVec, massVec));\n"
        "vec3 acceleration = mass1Factor * normalize(massVec) / massDist2;\n"

        "massVec = mass2Position.xyz - position;\n"
        "massDist2 = max(0.01, dot(massVec, massVec));\n"
        "acceleration += mass2Factor * normalize(massVec) / massDist2;\n"

        "massVec = mass3Position.xyz - position;\n"
        "massDist2 = max(0.01, dot(massVec, massVec));\n"
        "acceleration += mass3Factor * normalize(massVec) / massDist2;\n"

        "velocity += acceleration;\n"
        "velocity *= 0.9999;\n"

        "vPosition = position + velocity;\n"
        "vVelocity = velocity;\n"

        "vColor = aColor;\n"
        "gl_PointSize = 2.0;\n"
        "gl_Position = vec4(position, 1.0);\n"
    "}\n";

    const char* fsSource =
    "#version 450\n"
    "in vec3 vColor;\n"

    "out vec4 fragColor;\n"
    "void main() {\n"
        "fragColor = vec4(vColor, 0.3);\n"
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

    const char* tfVaryings[] = { "vPosition", "vVelocity" };

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glTransformFeedbackVaryings(program, 2, tfVaryings, GL_SEPARATE_ATTRIBS);
    glLinkProgram(program);

    params = -1;
    glGetProgramiv(program, GL_LINK_STATUS, &params);

    if (params != GL_TRUE) {
        printf("Program did not link!\n");
        exit(1);
    }

    glUseProgram(program);

    GLuint massUniformsLocation = glGetUniformBlockIndex(program, "Mass");
    glUniformBlockBinding(program, massUniformsLocation, 0);

    struct {
        float mass1Position[4];
        float mass2Position[4];
        float mass3Position[4];
        float mass1Factor;
        float mass2Factor;
        float mass3Factor;
    } massUniforms = {
        .mass1Position = { 
            ((float) rand() / RAND_MAX) * 2 - 1,
            ((float) rand() / RAND_MAX) * 2 - 1,
            ((float) rand() / RAND_MAX) * 2 - 1
        },
        .mass2Position = { 
            ((float) rand() / RAND_MAX) * 2 - 1,
            ((float) rand() / RAND_MAX) * 2 - 1,
            ((float) rand() / RAND_MAX) * 2 - 1
        },
        .mass3Position = { 
            ((float) rand() / RAND_MAX) * 2 - 1,
            ((float) rand() / RAND_MAX) * 2 - 1,
            ((float) rand() / RAND_MAX) * 2 - 1
        },
        .mass1Factor = ((float) rand() / RAND_MAX) / 30000,
        .mass2Factor = ((float) rand() / RAND_MAX) / 30000,
        .mass3Factor = ((float) rand() / RAND_MAX) / 30000
    };

    GLuint massUniformBuffer = 0;
    glGenBuffers(1, &massUniformBuffer);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, massUniformBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(massUniforms), &massUniforms, GL_STATIC_DRAW);


    GLuint currentVertexArray = vertexArrayA;
    GLuint currentTransformFeedback = transformFeedbackB;

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

        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(currentVertexArray);
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, currentTransformFeedback);
        
        glBeginTransformFeedback(GL_POINTS);
        glDrawArrays(GL_POINTS, 0, NUM_PARTICLES);
        glEndTransformFeedback();
        xogl_swapBuffers();

        if (currentVertexArray == vertexArrayA) {
            currentVertexArray = vertexArrayB;
            currentTransformFeedback = transformFeedbackA;
        } else {
            currentVertexArray = vertexArrayA;
            currentTransformFeedback = transformFeedbackB;
        }

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
