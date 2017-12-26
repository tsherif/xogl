#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <GL/glx.h>
#include "xogl.h"

//////////////////////////////////
// func is an OpenGL function, e.g: glBindVertexArray
// XOGL_GET_PROC(glBindVertexArray) =>
//     glBindVertexArray = (glBindVertexArrayProc) glXGetProcAddress((const GLubyte *) "glBindVertexArray");
//     if (!glBindVertexArray) fprintf(stderr, "Unable to get proc glBindVertexArray\n");
//////////////////////////////////
#define XOGL_GET_PROC(func)\
func = (func##Proc) glXGetProcAddress((const GLubyte *) #func);\
if (!func) fprintf(stderr, "Unable to get proc" #func "\n");\

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
static GLXContext ctx;

int xogl_init(Display* disp, Window win) {
    
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

    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddress((const GLubyte *) "glXCreateContextAttribsARB");

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

    XOGL_GET_PROC(glGenVertexArrays);
    XOGL_GET_PROC(glBindVertexArray);
    XOGL_GET_PROC(glGenBuffers);
    XOGL_GET_PROC(glBindBuffer);
    XOGL_GET_PROC(glBufferData);
    XOGL_GET_PROC(glVertexAttribPointer);
    XOGL_GET_PROC(glEnableVertexAttribArray);
    XOGL_GET_PROC(glCreateShader);
    XOGL_GET_PROC(glShaderSource);
    XOGL_GET_PROC(glCompileShader);
    XOGL_GET_PROC(glCreateProgram);
    XOGL_GET_PROC(glAttachShader);
    XOGL_GET_PROC(glLinkProgram);
    XOGL_GET_PROC(glUseProgram);
    XOGL_GET_PROC(glGetShaderiv);
    XOGL_GET_PROC(glGetProgramiv);
    XOGL_GET_PROC(glGetUniformLocation);
    XOGL_GET_PROC(glUniform1f);
    XOGL_GET_PROC(glUniform2f);
    XOGL_GET_PROC(glUniform3f);
    XOGL_GET_PROC(glUniform4f);
    XOGL_GET_PROC(glUniform1i);
    XOGL_GET_PROC(glUniform2i);
    XOGL_GET_PROC(glUniform3i);
    XOGL_GET_PROC(glUniform4i);
    XOGL_GET_PROC(glUniform1ui);
    XOGL_GET_PROC(glUniform2ui);
    XOGL_GET_PROC(glUniform3ui);
    XOGL_GET_PROC(glUniform4ui);
    XOGL_GET_PROC(glUniform1fv);
    XOGL_GET_PROC(glUniform2fv);
    XOGL_GET_PROC(glUniform3fv);
    XOGL_GET_PROC(glUniform4fv);
    XOGL_GET_PROC(glUniform1iv);
    XOGL_GET_PROC(glUniform2iv);
    XOGL_GET_PROC(glUniform3iv);
    XOGL_GET_PROC(glUniform4iv);
    XOGL_GET_PROC(glUniform1uiv);
    XOGL_GET_PROC(glUniform2uiv);
    XOGL_GET_PROC(glUniform3uiv);
    XOGL_GET_PROC(glUniform4uiv);
    XOGL_GET_PROC(glUniformMatrix2fv);
    XOGL_GET_PROC(glUniformMatrix3fv);
    XOGL_GET_PROC(glUniformMatrix4fv);
    XOGL_GET_PROC(glUniformMatrix2x3fv);
    XOGL_GET_PROC(glUniformMatrix3x2fv);
    XOGL_GET_PROC(glUniformMatrix2x4fv);
    XOGL_GET_PROC(glUniformMatrix4x2fv);
    XOGL_GET_PROC(glUniformMatrix3x4fv);
    XOGL_GET_PROC(glUniformMatrix4x3fv);

    return 0;
}

void xogl_swapBuffers(Display* disp, Window win) {
    glXSwapBuffers(disp, win);
}

void xogl_destroy(Display* disp) {
    glXMakeCurrent(disp, None, NULL);
    glXDestroyContext(disp, ctx);
}
