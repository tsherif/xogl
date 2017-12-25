#include <math.h>
#include <GL/gl.h>
#include "vec3.h"
#include "mat4.h"

static vec3 temp;

void vec3_set(vec3 v, GLfloat x, GLfloat y, GLfloat z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

GLfloat vec3_dot(vec3 v1, vec3 v2) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

GLfloat vec3_length(vec3 v) {
    return sqrt(vec3_dot(v, v));
}

void vec3_scale(vec3 v, GLfloat s) {
    v[0] *= s;
    v[1] *= s;
    v[2] *= s;
}

void vec3_normalize(vec3 v) {
    float l = vec3_length(v);
    v[0] /= l;
    v[1] /= l;
    v[2] /= l;
}

void vec3_add(vec3 out, vec3 v1, vec3 v2) {
    out[0] = v1[0] + v2[0];
    out[1] = v1[1] + v2[1];
    out[2] = v1[2] + v2[2];
}

void vec3_sub(vec3 out, vec3 v1, vec3 v2) {
    out[0] = v1[0] - v2[0];
    out[1] = v1[1] - v2[1];
    out[2] = v1[2] - v2[2];
}

void vec3_cross(vec3 out, vec3 v1, vec3 v2) {
    temp[0] = v1[1] * v2[2] - v1[2] * v2[1];
    temp[1] = v1[2] * v2[0] - v1[0] * v2[2];
    temp[2] = v1[0] * v2[1] - v1[1] * v2[0];

    out[0] = temp[0];
    out[1] = temp[1];
    out[2] = temp[2];
}
