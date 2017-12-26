#ifndef __XOGL_MATH__
#define __XOGL_MATH__

typedef float vec3[3];
typedef float mat4[16];

void math_setVec3(vec3 v, float x, float y, float z);
float math_dotVec3(vec3 v1, vec3 v2);
float math_lengthVec3(vec3 v);
void math_scaleVec3(vec3 v, float s);
void math_normalizeVec3(vec3 v);
void math_addVec3(vec3 out, vec3 v1, vec3 v2);
void math_subVec3(vec3 out, vec3 v1, vec3 v2);
void math_crossVec3(vec3 out, vec3 v1, vec3 v2);
void math_identityMat4(mat4 m);
void math_translationMat4(mat4 m, float x, float y, float z);
void math_scalingMat4(mat4 m, float x, float y, float z);
void math_rotationXMat4(mat4 m, float theta);
void math_rotationYMat4(mat4 m, float theta);
void math_rotationZMat4(mat4 m, float theta);
void math_multiplyMat4(mat4 result, mat4 m1, mat4 m2);
void math_mat4TransformVec3(vec3 out, mat4 m, vec3 v);
void math_mat4TransformVec4(float* out, mat4 m, float* v);
void math_transposeMat4(mat4 result, mat4 m);
float math_detMat4(mat4 m);
void math_invertMat4(mat4 result, mat4 m);
void math_lookAtMat4(mat4 m, vec3 eye, vec3 at, vec3 up);
void math_orthoMat4(mat4 m, float left, float right, float bottom, float top, float near, float far);
void math_perspectiveMat4(mat4 m, float yfov, float aspect, float near, float far);

#endif
