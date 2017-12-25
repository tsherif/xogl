#ifndef __VEC3__
#define __VEC3__

typedef GLfloat vec3[3];
void vec3_set(vec3, GLfloat, GLfloat, GLfloat);
GLfloat vec3_length(vec3);
void vec3_scale(vec3, GLfloat);
void vec3_normalize(vec3);
void vec3_add(vec3, vec3, vec3);
void vec3_sub(vec3, vec3, vec3);
GLfloat vec3_dot(vec3, vec3);
void vec3_cross(vec3, vec3, vec3);

#endif
