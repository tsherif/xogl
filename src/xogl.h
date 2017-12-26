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

#ifndef _OPENGL_H_
#define _OPENGL_H_

#include <GL/gl.h>

//////////////////////////////////
// ret is return value of OpenGL function
// func is an OpenGL function, e.g: glBindVertexArray
// XOGL_DECLARE_PROC(void, glBindVertexArray, GLsizei, GLuint *) =>
//     typedef void (*glBindVertexArrayProc)(GLsizei, GLuint *);
//     glBindVertexArrayProc glBindVertexArray;
//////////////////////////////////
#define XOGL_DECLARE_PROC(ret, func, ...)\
typedef ret (*func##Proc)(__VA_ARGS__);\
func##Proc func;\

// VBOs
XOGL_DECLARE_PROC(void, glGenBuffers, GLsizei, GLuint *);
XOGL_DECLARE_PROC(void, glBindBuffer, GLenum target, GLuint);
XOGL_DECLARE_PROC(void, glBufferData, GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);

// VAOs
XOGL_DECLARE_PROC(void, glGenVertexArrays, GLsizei, GLuint *);
XOGL_DECLARE_PROC(void, glBindVertexArray, GLuint);
XOGL_DECLARE_PROC(void, glVertexAttribPointer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer);
XOGL_DECLARE_PROC(void, glEnableVertexAttribArray, GLuint index);

// Programs
XOGL_DECLARE_PROC(GLuint, glCreateShader, GLenum type);
XOGL_DECLARE_PROC(void, glShaderSource, GLuint shader, GLsizei count, const GLchar* const *string, const GLint *length);
XOGL_DECLARE_PROC(void, glCompileShader, GLuint shader);
XOGL_DECLARE_PROC(void, glAttachShader, GLuint program, GLuint shader);
XOGL_DECLARE_PROC(void, glLinkProgram, GLuint program);
XOGL_DECLARE_PROC(void, glUseProgram, GLuint program);
XOGL_DECLARE_PROC(GLuint, glCreateProgram, void);
XOGL_DECLARE_PROC(void, glGetShaderiv, GLuint, GLenum, GLint *);
XOGL_DECLARE_PROC(void, glGetProgramiv, GLuint, GLenum, GLint *);

// Uniforms
XOGL_DECLARE_PROC(GLuint, glGetUniformLocation, GLuint, const GLchar*);
XOGL_DECLARE_PROC(void, glUniform1f, GLint location, GLfloat v0);
XOGL_DECLARE_PROC(void, glUniform2f, GLint location, GLfloat v0, GLfloat v1);
XOGL_DECLARE_PROC(void, glUniform3f, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
XOGL_DECLARE_PROC(void, glUniform4f, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
XOGL_DECLARE_PROC(void, glUniform1i, GLint location, GLint v0);
XOGL_DECLARE_PROC(void, glUniform2i, GLint location, GLint v0, GLint v1);
XOGL_DECLARE_PROC(void, glUniform3i, GLint location, GLint v0, GLint v1, GLint v2);
XOGL_DECLARE_PROC(void, glUniform4i, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
XOGL_DECLARE_PROC(void, glUniform1ui, GLint location, GLuint v0);
XOGL_DECLARE_PROC(void, glUniform2ui, GLint location, GLuint v0, GLuint v1);
XOGL_DECLARE_PROC(void, glUniform3ui, GLint location, GLuint v0, GLuint v1, GLuint v2);
XOGL_DECLARE_PROC(void, glUniform4ui, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
XOGL_DECLARE_PROC(void, glUniform1fv, GLint location, GLsizei count, const GLfloat *value);
XOGL_DECLARE_PROC(void, glUniform2fv, GLint location, GLsizei count, const GLfloat *value);
XOGL_DECLARE_PROC(void, glUniform3fv, GLint location, GLsizei count, const GLfloat *value);
XOGL_DECLARE_PROC(void, glUniform4fv, GLint location, GLsizei count, const GLfloat *value);
XOGL_DECLARE_PROC(void, glUniform1iv, GLint location, GLsizei count, const GLint *value);
XOGL_DECLARE_PROC(void, glUniform2iv, GLint location, GLsizei count, const GLint *value);
XOGL_DECLARE_PROC(void, glUniform3iv, GLint location, GLsizei count, const GLint *value);
XOGL_DECLARE_PROC(void, glUniform4iv, GLint location, GLsizei count, const GLint *value);
XOGL_DECLARE_PROC(void, glUniform1uiv,  GLint location, GLsizei count, const GLuint *value);
XOGL_DECLARE_PROC(void, glUniform2uiv,  GLint location, GLsizei count, const GLuint *value);
XOGL_DECLARE_PROC(void, glUniform3uiv,  GLint location, GLsizei count, const GLuint *value);
XOGL_DECLARE_PROC(void, glUniform4uiv,  GLint location, GLsizei count, const GLuint *value);
XOGL_DECLARE_PROC(void, glUniformMatrix2fv,  GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
XOGL_DECLARE_PROC(void, glUniformMatrix3fv,  GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
XOGL_DECLARE_PROC(void, glUniformMatrix4fv,  GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
XOGL_DECLARE_PROC(void, glUniformMatrix2x3fv, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
XOGL_DECLARE_PROC(void, glUniformMatrix3x2fv, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
XOGL_DECLARE_PROC(void, glUniformMatrix2x4fv, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
XOGL_DECLARE_PROC(void, glUniformMatrix4x2fv, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
XOGL_DECLARE_PROC(void, glUniformMatrix3x4fv, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
XOGL_DECLARE_PROC(void, glUniformMatrix4x3fv, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

int xogl_init(Display* disp, Window win, int major, int minor);
void xogl_destroy(Display* disp);
void xogl_swapBuffers(Display* disp, Window win);
#endif
