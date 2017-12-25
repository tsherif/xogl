#ifndef __MAT4__
#define __MAT4__

#include "vec3.h"

typedef GLfloat mat4[16];

void mat4_identity(mat4);
void mat4_translation(mat4, GLfloat, GLfloat, GLfloat);
void mat4_scaling(mat4, GLfloat, GLfloat, GLfloat);
void mat4_rotationX(mat4, GLfloat);
void mat4_rotationY(mat4, GLfloat);
void mat4_rotationZ(mat4, GLfloat);
void mat4_mult(mat4 result, mat4, mat4);
void mat4_multVec3(vec3, mat4, vec3);
void mat4_multVec4(GLfloat*, mat4, GLfloat*);
void mat4_transpose(mat4, mat4);
GLfloat mat4_det(mat4);
void mat4_invert(mat4, mat4);
void mat4_lookAt(mat4, vec3, vec3, vec3);
void mat4_ortho(mat4, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
void mat4_perspective(mat4, GLfloat, GLfloat, GLfloat, GLfloat);

#endif
