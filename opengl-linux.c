#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <time.h>
#include <unistd.h>
#include <GL/glx.h>
#include "opengl.h"

Display* disp;
Window win;
XEvent event;
XWindowAttributes xWinAtt;
int running = 0;

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
static GLXContext ctx;

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

int main(int argc, char const *argv[]) {
    // X Windows stuff
    disp = XOpenDisplay(NULL);

    if (disp == NULL) {
        printf("Unable to connect to X Server\n");
        return 1;
    }

    win = XCreateSimpleWindow(disp, DefaultRootWindow(disp), 20, 20, 1000, 1000, 0, 0, 0);
    

    XSelectInput(disp, win, ExposureMask | KeyPressMask | ButtonPressMask);
    XStoreName(disp, win, "Tarek's Bare-bones OpenGL App!");
    XMapWindow(disp, win);

    int numFBC = 0;
    GLint visualAtt[] = {
        GLX_RENDER_TYPE, GLX_RGBA_BIT, 
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT, 
        GLX_DOUBLEBUFFER, True, 
        GLX_RED_SIZE, 1,
        GLX_GREEN_SIZE, 1,
        GLX_BLUE_SIZE, 1,
        None
    };

    GLXFBConfig *fbc = glXChooseFBConfig(disp, DefaultScreen(disp), visualAtt, &numFBC);

    if (!fbc) {
        fprintf(stderr, "Unable to get framebuffer\n");
        return -1;        
    }

    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddress("glXCreateContextAttribsARB");

    if (!glXCreateContextAttribsARB) {
        fprintf(stderr, "Unable to get proc glXCreateContextAttribsARB\n");
        XFree(fbc);
        return -1; 
    }

    static int contextAttribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 5,
        GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
        GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        None
    };

    ctx = glXCreateContextAttribsARB(disp, *fbc, NULL, True, contextAttribs);

    XFree(fbc);

    if (!ctx) {
        fprintf(stderr, "Unable to create OpenGL context\n");
        return -1;
    }

    glXMakeCurrent(disp, win, ctx);

    glGenVertexArrays = (glGenVertexArraysProc) glXGetProcAddress("glGenVertexArrays");

    if (!glGenVertexArrays) {
        fprintf(stderr, "Unable to get proc glGenVertexArrays\n");
    }

    glBindVertexArray = (glBindVertexArrayProc) glXGetProcAddress((const GLubyte *) "glBindVertexArray");

    if (!glBindVertexArray) {
        fprintf(stderr, "Unable to get proc glBindVertexArray\n");
    }

    glGenBuffers = (glGenBuffersProc) glXGetProcAddress((const GLubyte *) "glGenBuffers");

    if (!glGenBuffers) {
        fprintf(stderr, "Unable to get proc glGenBuffers\n");
    }

    glBindBuffer = (glBindBufferProc) glXGetProcAddress((const GLubyte *) "glBindBuffer");

    if (!glBindBuffer) {
        fprintf(stderr, "Unable to get proc glBindBuffer\n");
    }

    glBufferData = (glBufferDataProc) glXGetProcAddress((const GLubyte *) "glBufferData");

    if (!glBufferData) {
        fprintf(stderr, "Unable to get proc glBufferData\n");
    }

    glVertexAttribPointer = (glVertexAttribPointerProc) glXGetProcAddress((const GLubyte *) "glVertexAttribPointer");

    if (!glVertexAttribPointer) {
        fprintf(stderr, "Unable to get proc glVertexAttribPointer\n");
    }

    glEnableVertexAttribArray = (glEnableVertexAttribArrayProc) glXGetProcAddress((const GLubyte *) "glEnableVertexAttribArray");

    if (!glEnableVertexAttribArray) {
        fprintf(stderr, "Unable to get proc glEnableVertexAttribArray\n");
    }

    glCreateShader = (glCreateShaderProc) glXGetProcAddress((const GLubyte *) "glCreateShader");

    if (!glCreateShader) {
        fprintf(stderr, "Unable to get proc glCreateShader\n");
    }

    glShaderSource = (glShaderSourceProc) glXGetProcAddress((const GLubyte *) "glShaderSource");

    if (!glShaderSource) {
        fprintf(stderr, "Unable to get proc glShaderSource\n");
    }

    glCompileShader = (glCompileShaderProc) glXGetProcAddress((const GLubyte *) "glCompileShader");

    if (!glCompileShader) {
        fprintf(stderr, "Unable to get proc glCompileShader\n");
    }

    glCreateProgram = (glCreateProgramProc) glXGetProcAddress((const GLubyte *) "glCreateProgram");

    if (!glCreateProgram) {
        fprintf(stderr, "Unable to get proc glCreateProgram\n");
    }

    glAttachShader = (glAttachShaderProc) glXGetProcAddress((const GLubyte *) "glAttachShader");

    if (!glAttachShader) {
        fprintf(stderr, "Unable to get proc glAttachShader\n");
    }

    glLinkProgram = (glLinkProgramProc) glXGetProcAddress((const GLubyte *) "glLinkProgram");

    if (!glLinkProgram) {
        fprintf(stderr, "Unable to get proc glLinkProgram\n");
    }

    glUseProgram = (glUseProgramProc) glXGetProcAddress((const GLubyte *) "glUseProgram");

    if (!glUseProgram) {
        fprintf(stderr, "Unable to get proc glUseProgram\n");
    }

    glGetShaderiv = (glGetShaderivProc) glXGetProcAddress((const GLubyte *) "glGetShaderiv");

    if (!glGetShaderiv) {
        fprintf(stderr, "Unable to get proc glGetShaderiv\n");
    }

    glGetProgramiv = (glGetProgramivProc) glXGetProcAddress((const GLubyte *) "glGetProgramiv");

    if (!glGetProgramiv) {
        fprintf(stderr, "Unable to get proc glGetProgramiv\n");
    }

    glGetUniformLocation = (glGetUniformLocationProc) glXGetProcAddress((const GLubyte *) "glGetUniformLocation");

    if (!glGetUniformLocation) {
        fprintf(stderr, "Unable to get proc glGetUniformLocation\n");
    }

    glUniform1f = (glUniform1fProc) glXGetProcAddress((const GLubyte *) "glUniform1f");

    if (!glUniform1f) {
        fprintf(stderr, "Unable to get proc glUniform1f\n");
    }

    RendererInit();

    running = 1;
    float frameTime = 1000.0 / 60.0; 
    double startTime, endTime;

    // Animation loop
    while (1) {
        startTime = getTime();    

        if (XCheckWindowEvent(disp, win, ExposureMask | KeyPressMask, &event) == True) {
            RendererEvent rEvent = {};


            if (event.type == Expose) {
                XGetWindowAttributes(disp, win, &xWinAtt);
                glViewport(0, 0, xWinAtt.width, xWinAtt.height);
            }

            if (event.type == KeyPress) {
                rEvent.type = RENDERER_KEY_PRESS;
                KeySym key = XLookupKeysym(&event.xkey, 0);
                
                int parsed = 0;

                if (key >= XK_space && key <= XK_asciitilde) {
                    rEvent.key = key;
                    parsed = 1;
                }

                if (key == XK_Left) {
                    rEvent.key = RENDERER_KEY_LEFT;
                    parsed = 1;
                }

                if (key == XK_Right) {
                    rEvent.key = RENDERER_KEY_RIGHT;
                    parsed = 1;
                }

                if (key == XK_Up) {
                    rEvent.key = RENDERER_KEY_UP;
                    parsed = 1;
                }

                if (key == XK_Down) {
                    rEvent.key = RENDERER_KEY_DOWN;
                    parsed = 1;
                }

                if (parsed) {
                    RendererInput(rEvent);
                }
            }
        }

        if (!running) {
            break;
        }

        RendererMain(startTime);

        glXSwapBuffers(disp, win);

        endTime = getTime();
        double elapsed = endTime - startTime;
        if (elapsed < frameTime) {
            milisleep(frameTime - elapsed);
            endTime = getTime();
        }
    };

    // Teardown
    glXMakeCurrent(disp, None, NULL);
    glXDestroyContext(disp, ctx);
    XDestroyWindow(disp, win);
    XCloseDisplay(disp);
    printf("Done!\n");

    return 0;
}

void StopRenderLoop() {
    running = 0;
}
