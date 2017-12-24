#include <stdio.h>
#include <GL/glx.h>
#include "opengl.h"


typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
static GLXContext ctx;

int openGLInit(Display* disp, Window win, int major, int minor) {
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

    contextAttribs[1] = major;
    contextAttribs[3] = minor;

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
        openGLDestroy(disp);
        return -1; 
    }

    glBindVertexArray = (glBindVertexArrayProc) glXGetProcAddress((const GLubyte *) "glBindVertexArray");

    if (!glBindVertexArray) {
        fprintf(stderr, "Unable to get proc glBindVertexArray\n");
        openGLDestroy(disp);
        return -1; 
    }

    glGenBuffers = (glGenBuffersProc) glXGetProcAddress((const GLubyte *) "glGenBuffers");

    if (!glGenBuffers) {
        fprintf(stderr, "Unable to get proc glGenBuffers\n");
        openGLDestroy(disp);
        return -1; 
    }

    glBindBuffer = (glBindBufferProc) glXGetProcAddress((const GLubyte *) "glBindBuffer");

    if (!glBindBuffer) {
        fprintf(stderr, "Unable to get proc glBindBuffer\n");
        openGLDestroy(disp);
        return -1; 
    }

    glBufferData = (glBufferDataProc) glXGetProcAddress((const GLubyte *) "glBufferData");

    if (!glBufferData) {
        fprintf(stderr, "Unable to get proc glBufferData\n");
        openGLDestroy(disp);
        return -1; 
    }

    glVertexAttribPointer = (glVertexAttribPointerProc) glXGetProcAddress((const GLubyte *) "glVertexAttribPointer");

    if (!glVertexAttribPointer) {
        fprintf(stderr, "Unable to get proc glVertexAttribPointer\n");
        openGLDestroy(disp);
        return -1; 
    }

    glEnableVertexAttribArray = (glEnableVertexAttribArrayProc) glXGetProcAddress((const GLubyte *) "glEnableVertexAttribArray");

    if (!glEnableVertexAttribArray) {
        fprintf(stderr, "Unable to get proc glEnableVertexAttribArray\n");
        openGLDestroy(disp);
        return -1; 
    }

    glCreateShader = (glCreateShaderProc) glXGetProcAddress((const GLubyte *) "glCreateShader");

    if (!glCreateShader) {
        fprintf(stderr, "Unable to get proc glCreateShader\n");
        openGLDestroy(disp);
        return -1; 
    }

    glShaderSource = (glShaderSourceProc) glXGetProcAddress((const GLubyte *) "glShaderSource");

    if (!glShaderSource) {
        fprintf(stderr, "Unable to get proc glShaderSource\n");
        openGLDestroy(disp);
        return -1; 
    }

    glCompileShader = (glCompileShaderProc) glXGetProcAddress((const GLubyte *) "glCompileShader");

    if (!glCompileShader) {
        fprintf(stderr, "Unable to get proc glCompileShader\n");
        openGLDestroy(disp);
        return -1; 
    }

    glCreateProgram = (glCreateProgramProc) glXGetProcAddress((const GLubyte *) "glCreateProgram");

    if (!glCreateProgram) {
        fprintf(stderr, "Unable to get proc glCreateProgram\n");
        openGLDestroy(disp);
        return -1; 
    }

    glAttachShader = (glAttachShaderProc) glXGetProcAddress((const GLubyte *) "glAttachShader");

    if (!glAttachShader) {
        fprintf(stderr, "Unable to get proc glAttachShader\n");
        openGLDestroy(disp);
        return -1; 
    }

    glLinkProgram = (glLinkProgramProc) glXGetProcAddress((const GLubyte *) "glLinkProgram");

    if (!glLinkProgram) {
        fprintf(stderr, "Unable to get proc glLinkProgram\n");
        openGLDestroy(disp);
        return -1; 
    }

    glUseProgram = (glUseProgramProc) glXGetProcAddress((const GLubyte *) "glUseProgram");

    if (!glUseProgram) {
        fprintf(stderr, "Unable to get proc glUseProgram\n");
        openGLDestroy(disp);
        return -1; 
    }

    glGetShaderiv = (glGetShaderivProc) glXGetProcAddress((const GLubyte *) "glGetShaderiv");

    if (!glGetShaderiv) {
        fprintf(stderr, "Unable to get proc glGetShaderiv\n");
        openGLDestroy(disp);
        return -1; 
    }

    glGetProgramiv = (glGetProgramivProc) glXGetProcAddress((const GLubyte *) "glGetProgramiv");

    if (!glGetProgramiv) {
        fprintf(stderr, "Unable to get proc glGetProgramiv\n");
        openGLDestroy(disp);
        return -1; 
    }

    return 0;
}

void openGLSwapBuffers(Display* disp, Window win) {
    glXSwapBuffers(disp, win);
}

void openGLDestroy(Display* disp) {
    glXMakeCurrent(disp, None, NULL);
    glXDestroyContext(disp, ctx);
}
