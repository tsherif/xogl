#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <time.h>
#include <unistd.h>
#include "opengl.h"

Display* disp;
Window win;
XEvent event;
Colormap cmap;
XWindowAttributes xWinAtt;

double getTime() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1000000.0;
}

void milisleep(float ms) {
    struct timespec ts;
    ts.tv_sec = (time_t) (ms / 1000.0);
    ts.tv_nsec = (long) ((ms - (ts.tv_sec * 1000)) * 1000000);
    nanosleep(&ts, 0);
}

int main(int argc, char** argv) {

    // X Windows stuff
    disp = XOpenDisplay(NULL);

    if (disp == NULL) {
        printf("Unable to connect to X Server\n");
        return 1;
    }

    win = XCreateSimpleWindow(disp, DefaultRootWindow(disp), 20, 20, 1000, 1000, 0, 0, 0);
    

    XSelectInput(disp, win, ExposureMask | KeyPressMask);
    XStoreName(disp, win, "Tarek's Bare-bones OpenGL App!");
    XMapWindow(disp, win);

    // Start OpenGL Stuff
    openGLInit(disp, win, 4, 5);

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
    "out vec3 vColor;\n"
    "void main() {\n"
    "    vColor = color;\n"
    "    gl_Position = vec4(position, 0.0, 1.0);\n"
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

    GLuint tex = 0;
    glGenTextures(1, &tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        64,
        64,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        0
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    float frameTime = 1000.0 / 60.0; 
    double startTime, endTime;

    // Animation loop
    while (1) {
        startTime = getTime();    

        // XNextEvent(disp, &event);

        // if (event.type == Expose) {
        //     XGetWindowAttributes(disp, win, &xWinAtt);
        //     glViewport(0, 0, xWinAtt.width, xWinAtt.height);
        //     glClear(GL_COLOR_BUFFER_BIT);
        //     glDrawArrays(GL_TRIANGLES, 0, 3);
        //     openGLSwapBuffers(disp, win);
        // }

        // if (event.type == KeyPress) {
        //     break;
        // }
        endTime = getTime();
        double elapsed = endTime - startTime;
        if (elapsed < frameTime) {
            milisleep(frameTime - elapsed);
            endTime = getTime();
        }
        printf("Elapsed time: %f\n",  endTime - startTime);
        sleep(1);
    };

    // Teardown
    openGLDestroy(disp);
    XDestroyWindow(disp, win);
    XCloseDisplay(disp);
    printf("Done!\n");
}
