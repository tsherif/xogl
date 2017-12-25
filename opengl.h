#ifndef _OPENGL_H_
#define _OPENGL_H_

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

typedef GLuint (*glCreateProgramProc)(void); 
glCreateProgramProc glCreateProgram;

typedef void (*glGetShaderivProc)(GLuint, GLenum, GLint *);
glGetShaderivProc glGetShaderiv;

typedef void (*glGetProgramivProc)(GLuint, GLenum, GLint *);
glGetProgramivProc glGetProgramiv;

// Uniforms
typedef GLuint (*glGetUniformLocationProc)(GLuint, const GLchar*);
glGetUniformLocationProc glGetUniformLocation;

typedef void (*glUniform1fProc)(GLint location, GLfloat v0);
glUniform1fProc glUniform1f;
 
typedef void (*glUniform2fProc)(GLint location, GLfloat v0, GLfloat v1);
glUniform2fProc glUniform2f;
 
typedef void (*glUniform3fProc)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
glUniform3fProc glUniform3f;
 
typedef void (*glUniform4fProc)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
glUniform4fProc glUniform4f;
 
typedef void (*glUniform1iProc)(GLint location, GLint v0);
glUniform1iProc glUniform1i;
 
typedef void (*glUniform2iProc)(GLint location, GLint v0, GLint v1);
glUniform2iProc glUniform2i;
 
typedef void (*glUniform3iProc)(GLint location, GLint v0, GLint v1, GLint v2);
glUniform3iProc glUniform3i;
 
typedef void (*glUniform4iProc)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
glUniform4iProc glUniform4i;
 
typedef void (*glUniform1uiProc)(GLint location, GLuint v0);
glUniform1uiProc glUniform1ui;
 
typedef void (*glUniform2uiProc)(GLint location, GLuint v0, GLuint v1);
glUniform2uiProc glUniform2ui;
 
typedef void (*glUniform3uiProc)(GLint location, GLuint v0, GLuint v1, GLuint v2);
glUniform3uiProc glUniform3ui;
 
typedef void (*glUniform4uiProc)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
glUniform4uiProc glUniform4ui;
 
typedef void (*glUniform1fvProc)(GLint location, GLsizei count, const GLfloat *value);
glUniform1fvProc glUniform1fv;
 
typedef void (*glUniform2fvProc)(GLint location, GLsizei count, const GLfloat *value);
glUniform2fvProc glUniform2fv;
 
typedef void (*glUniform3fvProc)(GLint location, GLsizei count, const GLfloat *value);
glUniform3fvProc glUniform3fv;
 
typedef void (*glUniform4fvProc)(GLint location, GLsizei count, const GLfloat *value);
glUniform4fvProc glUniform4fv;
 
typedef void (*glUniform1ivProc)(GLint location, GLsizei count, const GLint *value);
glUniform1ivProc glUniform1iv;
 
typedef void (*glUniform2ivProc)(GLint location, GLsizei count, const GLint *value);
glUniform2ivProc glUniform2iv;
 
typedef void (*glUniform3ivProc)(GLint location, GLsizei count, const GLint *value);
glUniform3ivProc glUniform3iv;
 
typedef void (*glUniform4ivProc)(GLint location, GLsizei count, const GLint *value);
glUniform4ivProc glUniform4iv;
 
typedef void (*glUniform1uivProc)( GLint location, GLsizei count, const GLuint *value);
glUniform1uivProc glUniform1uiv;
 
typedef void (*glUniform2uivProc)( GLint location, GLsizei count, const GLuint *value);
glUniform2uivProc glUniform2uiv;
 
typedef void (*glUniform3uivProc)( GLint location, GLsizei count, const GLuint *value);
glUniform3uivProc glUniform3uiv;
 
typedef void (*glUniform4uivProc)( GLint location, GLsizei count, const GLuint *value);
glUniform4uivProc glUniform4uiv;
 
typedef void (*glUniformMatrix2fvProc)( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
glUniformMatrix2fvProc glUniformMatrix2fv;
 
typedef void (*glUniformMatrix3fvProc)( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
glUniformMatrix3fvProc glUniformMatrix3fv;
 
typedef void (*glUniformMatrix4fvProc)( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
glUniformMatrix4fvProc glUniformMatrix4fv;
 
typedef void (*glUniformMatrix2x3fvProc)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
glUniformMatrix2x3fvProc glUniformMatrix2x3fv;
 
typedef void (*glUniformMatrix3x2fvProc)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
glUniformMatrix3x2fvProc glUniformMatrix3x2fv;
 
typedef void (*glUniformMatrix2x4fvProc)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
glUniformMatrix2x4fvProc glUniformMatrix2x4fv;
 
typedef void (*glUniformMatrix4x2fvProc)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
glUniformMatrix4x2fvProc glUniformMatrix4x2fv;
 
typedef void (*glUniformMatrix3x4fvProc)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
glUniformMatrix3x4fvProc glUniformMatrix3x4fv;
 
typedef void (*glUniformMatrix4x3fvProc)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
glUniformMatrix4x3fvProc glUniformMatrix4x3fv;

#define RENDERER_KEY_PRESS 1
#define RENDERER_BUTTON_PRESS 2
#define RENDERER_KEY_LEFT   0xFF01
#define RENDERER_KEY_RIGHT  0xFF02
#define RENDERER_KEY_UP     0xFF03
#define RENDERER_KEY_DOWN   0xFF04

typedef struct {
    unsigned int type;
    unsigned int key;
    unsigned int mouseX;
    unsigned int mouseY;
    unsigned char mouseButtons;
} RendererEvent;

// Renderer functions
void RendererInit(void);
void RendererMain(double time);
void RendererInput(RendererEvent);

// Platform functions
void StopRenderLoop(void);

#endif
