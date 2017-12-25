#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <GL/glx.h>
#include "opengl.h"

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
static GLXContext ctx;

int initOpenGL(Display* disp, Window win) {
    
    int numFBC = 0;
    GLint visualAtt[] = {
        GLX_RENDER_TYPE, GLX_RGBA_BIT, 
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT, 
        GLX_DOUBLEBUFFER, True, 
        GLX_RED_SIZE, 1,
        GLX_GREEN_SIZE, 1,
        GLX_BLUE_SIZE, 1,
        GLX_DEPTH_SIZE, 1,
        GLX_STENCIL_SIZE, 1,
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

    glUniform2f = (glUniform2fProc) glXGetProcAddress((const GLubyte *) "glUniform2f");

    if (!glUniform2f) {
        fprintf(stderr, "Unable to get proc glUniform2f\n");
    }

    glUniform3f = (glUniform3fProc) glXGetProcAddress((const GLubyte *) "glUniform3f");

    if (!glUniform3f) {
        fprintf(stderr, "Unable to get proc glUniform3f\n");
    }

    glUniform4f = (glUniform4fProc) glXGetProcAddress((const GLubyte *) "glUniform4f");

    if (!glUniform4f) {
        fprintf(stderr, "Unable to get proc glUniform4f\n");
    }

    glUniform1i = (glUniform1iProc) glXGetProcAddress((const GLubyte *) "glUniform1i");

    if (!glUniform1i) {
        fprintf(stderr, "Unable to get proc glUniform1i\n");
    }

    glUniform2i = (glUniform2iProc) glXGetProcAddress((const GLubyte *) "glUniform2i");

    if (!glUniform2i) {
        fprintf(stderr, "Unable to get proc glUniform2i\n");
    }

    glUniform3i = (glUniform3iProc) glXGetProcAddress((const GLubyte *) "glUniform3i");

    if (!glUniform3i) {
        fprintf(stderr, "Unable to get proc glUniform3i\n");
    }

    glUniform4i = (glUniform4iProc) glXGetProcAddress((const GLubyte *) "glUniform4i");

    if (!glUniform4i) {
        fprintf(stderr, "Unable to get proc glUniform4i\n");
    }

    glUniform1ui = (glUniform1uiProc) glXGetProcAddress((const GLubyte *) "glUniform1ui");

    if (!glUniform1ui) {
        fprintf(stderr, "Unable to get proc glUniform1ui\n");
    }

    glUniform2ui = (glUniform2uiProc) glXGetProcAddress((const GLubyte *) "glUniform2ui");

    if (!glUniform2ui) {
        fprintf(stderr, "Unable to get proc glUniform2ui\n");
    }

    glUniform3ui = (glUniform3uiProc) glXGetProcAddress((const GLubyte *) "glUniform3ui");

    if (!glUniform3ui) {
        fprintf(stderr, "Unable to get proc glUniform3ui\n");
    }

    glUniform4ui = (glUniform4uiProc) glXGetProcAddress((const GLubyte *) "glUniform4ui");

    if (!glUniform4ui) {
        fprintf(stderr, "Unable to get proc glUniform4ui\n");
    }

    glUniform1fv = (glUniform1fvProc) glXGetProcAddress((const GLubyte *) "glUniform1fv");

    if (!glUniform1fv) {
        fprintf(stderr, "Unable to get proc glUniform1fv\n");
    }

    glUniform2fv = (glUniform2fvProc) glXGetProcAddress((const GLubyte *) "glUniform2fv");

    if (!glUniform2fv) {
        fprintf(stderr, "Unable to get proc glUniform2fv\n");
    }

    glUniform3fv = (glUniform3fvProc) glXGetProcAddress((const GLubyte *) "glUniform3fv");

    if (!glUniform3fv) {
        fprintf(stderr, "Unable to get proc glUniform3fv\n");
    }

    glUniform4fv = (glUniform4fvProc) glXGetProcAddress((const GLubyte *) "glUniform4fv");

    if (!glUniform4fv) {
        fprintf(stderr, "Unable to get proc glUniform4fv\n");
    }

    glUniform1iv = (glUniform1ivProc) glXGetProcAddress((const GLubyte *) "glUniform1iv");

    if (!glUniform1iv) {
        fprintf(stderr, "Unable to get proc glUniform1iv\n");
    }

    glUniform2iv = (glUniform2ivProc) glXGetProcAddress((const GLubyte *) "glUniform2iv");

    if (!glUniform2iv) {
        fprintf(stderr, "Unable to get proc glUniform2iv\n");
    }

    glUniform3iv = (glUniform3ivProc) glXGetProcAddress((const GLubyte *) "glUniform3iv");

    if (!glUniform3iv) {
        fprintf(stderr, "Unable to get proc glUniform3iv\n");
    }

    glUniform4iv = (glUniform4ivProc) glXGetProcAddress((const GLubyte *) "glUniform4iv");

    if (!glUniform4iv) {
        fprintf(stderr, "Unable to get proc glUniform4iv\n");
    }

    glUniform1uiv = (glUniform1uivProc) glXGetProcAddress((const GLubyte *) "glUniform1uiv");

    if (!glUniform1uiv) {
        fprintf(stderr, "Unable to get proc glUniform1uiv\n");
    }

    glUniform2uiv = (glUniform2uivProc) glXGetProcAddress((const GLubyte *) "glUniform2uiv");

    if (!glUniform2uiv) {
        fprintf(stderr, "Unable to get proc glUniform2uiv\n");
    }

    glUniform3uiv = (glUniform3uivProc) glXGetProcAddress((const GLubyte *) "glUniform3uiv");

    if (!glUniform3uiv) {
        fprintf(stderr, "Unable to get proc glUniform3uiv\n");
    }

    glUniform4uiv = (glUniform4uivProc) glXGetProcAddress((const GLubyte *) "glUniform4uiv");

    if (!glUniform4uiv) {
        fprintf(stderr, "Unable to get proc glUniform4uiv\n");
    }

    glUniformMatrix2fv = (glUniformMatrix2fvProc) glXGetProcAddress((const GLubyte *) "glUniformMatrix2fv");

    if (!glUniformMatrix2fv) {
        fprintf(stderr, "Unable to get proc glUniformMatrix2fv\n");
    }

    glUniformMatrix3fv = (glUniformMatrix3fvProc) glXGetProcAddress((const GLubyte *) "glUniformMatrix3fv");

    if (!glUniformMatrix3fv) {
        fprintf(stderr, "Unable to get proc glUniformMatrix3fv\n");
    }

    glUniformMatrix4fv = (glUniformMatrix4fvProc) glXGetProcAddress((const GLubyte *) "glUniformMatrix4fv");

    if (!glUniformMatrix4fv) {
        fprintf(stderr, "Unable to get proc glUniformMatrix4fv\n");
    }

    glUniformMatrix2x3fv = (glUniformMatrix2x3fvProc) glXGetProcAddress((const GLubyte *) "glUniformMatrix2x3fv");

    if (!glUniformMatrix2x3fv) {
        fprintf(stderr, "Unable to get proc glUniformMatrix2x3fv\n");
    }

    glUniformMatrix3x2fv = (glUniformMatrix3x2fvProc) glXGetProcAddress((const GLubyte *) "glUniformMatrix3x2fv");

    if (!glUniformMatrix3x2fv) {
        fprintf(stderr, "Unable to get proc glUniformMatrix3x2fv\n");
    }

    glUniformMatrix2x4fv = (glUniformMatrix2x4fvProc) glXGetProcAddress((const GLubyte *) "glUniformMatrix2x4fv");

    if (!glUniformMatrix2x4fv) {
        fprintf(stderr, "Unable to get proc glUniformMatrix2x4fv\n");
    }

    glUniformMatrix4x2fv = (glUniformMatrix4x2fvProc) glXGetProcAddress((const GLubyte *) "glUniformMatrix4x2fv");

    if (!glUniformMatrix4x2fv) {
        fprintf(stderr, "Unable to get proc glUniformMatrix4x2fv\n");
    }

    glUniformMatrix3x4fv = (glUniformMatrix3x4fvProc) glXGetProcAddress((const GLubyte *) "glUniformMatrix3x4fv");

    if (!glUniformMatrix3x4fv) {
        fprintf(stderr, "Unable to get proc glUniformMatrix3x4fv\n");
    }

    glUniformMatrix4x3fv = (glUniformMatrix4x3fvProc) glXGetProcAddress((const GLubyte *) "glUniformMatrix4x3fv");

    if (!glUniformMatrix4x3fv) {
        fprintf(stderr, "Unable to get proc glUniformMatrix4x3fv\n");
    }

    return 0;
}

void swapBuffers(Display* disp, Window win) {
    glXSwapBuffers(disp, win);
}

void destroyOpenGL(Display* disp) {
    glXMakeCurrent(disp, None, NULL);
    glXDestroyContext(disp, ctx);
}
