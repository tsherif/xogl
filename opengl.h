#ifndef _OPENGL_H_
#define _OPENGL_H_

#include <X11/Xlib.h>
#include <GL/gl.h>

// VBOs
typedef void (*glGenBuffersProc)(GLsizei, GLuint *);
glGenBuffersProc glGenBuffers;

typedef void (*glBindBufferProc)(GLenum target, GLuint); 
glBindBufferProc glBindBuffer;

typedef void (*glBufferDataProc)(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage); 
glBufferDataProc glBufferData;


// VAOs
typedef void (*glGenVertexArraysProc)(GLsizei, GLuint *);
glGenVertexArraysProc glGenVertexArrays;

typedef void (*glBindVertexArrayProc)(GLuint); 
glBindVertexArrayProc glBindVertexArray;

typedef void (*glVertexAttribPointerProc)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer); 
glVertexAttribPointerProc glVertexAttribPointer;

typedef void (*glEnableVertexAttribArrayProc)(GLuint index); 
glEnableVertexAttribArrayProc glEnableVertexAttribArray;


// Programs
typedef GLuint (*glCreateShaderProc)(GLenum type); 
glCreateShaderProc glCreateShader;

typedef void (*glShaderSourceProc)(GLuint shader, GLsizei count, const GLchar* const *string, const GLint *length); 
glShaderSourceProc glShaderSource;

typedef void (*glCompileShaderProc)(GLuint shader); 
glCompileShaderProc glCompileShader;

typedef void (*glAttachShaderProc)(GLuint program, GLuint shader); 
glAttachShaderProc glAttachShader;

typedef void (*glLinkProgramProc)(GLuint program); 
glLinkProgramProc glLinkProgram;

typedef void (*glUseProgramProc)(GLuint program); 
glUseProgramProc glUseProgram;

typedef GLuint (*glCreateProgramProc)(); 
glCreateProgramProc glCreateProgram;

typedef void (*glGetShaderivProc)(GLuint, GLenum, GLint *);
glGetShaderivProc glGetShaderiv;

typedef void (*glGetProgramivProc)(GLuint, GLenum, GLint *);
glGetProgramivProc glGetProgramiv;


int openGLInit(Display*, Window, int major, int minor);
void openGLSwapBuffers(Display*, Window);
void openGLDestroy(Display*);

#endif
