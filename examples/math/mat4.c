#include <math.h>
#include <GL/gl.h>
#include "vec3.h"
#include "mat4.h"

static mat4 temp;

void mat4_identity(mat4 m) {
    m[0]  = 1;
    m[1]  = 0;
    m[2]  = 0;
    m[3]  = 0;

    m[4]  = 0;
    m[5]  = 1;
    m[6]  = 0;
    m[7]  = 0;

    m[8]  = 0;
    m[9]  = 0;
    m[10] = 1;
    m[11] = 0;

    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
}

void mat4_translation(mat4 m, GLfloat x, GLfloat y, GLfloat z) {
    m[0]  = 1;
    m[1]  = 0;
    m[2]  = 0;
    m[3]  = 0;

    m[4]  = 0;
    m[5]  = 1;
    m[6]  = 0;
    m[7]  = 0;

    m[8]  = 0;
    m[9]  = 0;
    m[10] = 1;
    m[11] = 0;

    m[12] = x;
    m[13] = y;
    m[14] = z;
    m[15] = 1;
}

void mat4_scaling(mat4 m, GLfloat x, GLfloat y, GLfloat z) {
    m[0]  = x;
    m[1]  = 0;
    m[2]  = 0;
    m[3]  = 0;

    m[4]  = 0;
    m[5]  = y;
    m[6]  = 0;
    m[7]  = 0;

    m[8]  = 0;
    m[9]  = 0;
    m[10] = z;
    m[11] = 0;

    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
}

void mat4_rotationX(mat4 m, GLfloat theta) {
    GLfloat sine = sin(theta);
    GLfloat cosine = cos(theta);

    m[0]  = 1;
    m[1]  = 0;
    m[2]  = 0;
    m[3]  = 0;

    m[4]  = 0;
    m[5]  = cosine;
    m[6]  = sine;
    m[7]  = 0;

    m[8]  = 0;
    m[9]  = -sine;
    m[10] = cosine;
    m[11] = 0;

    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
}

void mat4_rotationY(mat4 m, GLfloat theta) {
    GLfloat sine = sin(theta);
    GLfloat cosine = cos(theta);

    m[0]  = cosine;
    m[1]  = 0;
    m[2]  = -sine;
    m[3]  = 0;

    m[4]  = 0;
    m[5]  = 1;
    m[6]  = 0;
    m[7]  = 0;

    m[8]  = sine;
    m[9]  = 0;
    m[10] = cosine;
    m[11] = 0;

    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
}

void mat4_rotationZ(mat4 m, GLfloat theta) {
    GLfloat sine = sin(theta);
    GLfloat cosine = cos(theta);

    m[0]  = cosine;
    m[1]  = sine;
    m[2]  = 0;
    m[3]  = 0;

    m[4]  = -sine;
    m[5]  = cosine;
    m[6]  = 0;
    m[7]  = 0;

    m[8]  = 0;
    m[9]  = 0;
    m[10] = 1;
    m[11] = 0;

    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
}

void mat4_mult(mat4 result, mat4 m1, mat4 m2) {
    int row, col, i;
    int result_index, m1_index, m2_index;
    GLfloat val;

    for (col = 0; col < 4; col++) {
        for (row = 0; row < 4; row++) {
            result_index = col * 4 + row;
            val = 0;

            for (i = 0; i < 4; i++) {
                m1_index = i   * 4 + row;
                m2_index = col * 4 + i;

                val += m1[m1_index] * m2[m2_index];
            }

            temp[result_index] = val;
        }
    }

    for (i = 0; i < 16; i++) {
        result[i] = temp[i];
    }
}

void mat4_multVec3(vec3 out, mat4 m, vec3 v) {
    temp[0] = v[0] * m[0] + v[1] * m[4] + v[2] * m[8]  + m[12];
    temp[1] = v[0] * m[1] + v[1] * m[5] + v[2] * m[9]  + m[13];
    temp[2] = v[0] * m[2] + v[1] * m[6] + v[2] * m[10] + m[14];

    out[0] = temp[0];
    out[1] = temp[1];
    out[2] = temp[2];
}

void mat4_multVec4(GLfloat* out, mat4 m, GLfloat* v) {
    temp[0] = v[0] * m[0] + v[1] * m[4] + v[2] * m[8]  + v[3] * m[12];
    temp[1] = v[0] * m[1] + v[1] * m[5] + v[2] * m[9]  + v[3] * m[13];
    temp[2] = v[0] * m[2] + v[1] * m[6] + v[2] * m[10] + v[3] * m[14];
    temp[3] = v[0] * m[3] + v[1] * m[7] + v[2] * m[11] + v[3] * m[15];

    out[0] = temp[0];
    out[1] = temp[1];
    out[2] = temp[2];
    out[3] = temp[3];
}

void mat4_transpose(mat4 result, mat4 m) {
    int row, col;
    int index1, index2;

    for (col = 0; col < 4; col++) {
        for (row = col; row < 4; row++) {

            index1 = col * 4 + row;
            index2 = row * 4 + col;
            result[index1] = m[index2];
            result[index2] = m[index1];

        }
    }
}

GLfloat mat4_det(mat4 m) {
    GLfloat m0 = m[0];
    GLfloat m1 = m[1];
    GLfloat m2 = m[2];
    GLfloat m3 = m[3];
    GLfloat m4 = m[4];
    GLfloat m5 = m[5];
    GLfloat m6 = m[6];
    GLfloat m7 = m[7];
    GLfloat m8 = m[8];
    GLfloat m9 = m[9];
    GLfloat m10 = m[10];
    GLfloat m11 = m[11];
    GLfloat m12 = m[12];
    GLfloat m13 = m[13];
    GLfloat m14 = m[14];
    GLfloat m15 = m[15];

    return m0 * m5 * m10 * m15 +
    m0 * m9 * m14 * m7 +
    m0 * m13 * m6 * m11 +

    m4 * m1 * m14 * m11 +
    m4 * m9 * m2 * m15 +
    m4 * m13 * m10 * m3 +

    m8 * m1 * m6 * m15 +
    m8 * m5 * m14 * m3 +
    m8 * m13 * m2 * m7 +

    m12 * m1 * m10 * m7 +
    m12 * m5 * m2 * m11 +
    m12 * m9 * m6 * m3 -

    m0 * m5 * m14 * m11 -
    m0 * m9 * m6 * m15 -
    m0 * m13 * m10 * m7 -

    m4 * m1 * m10 * m15 -
    m4 * m9 * m14 * m3 -
    m4 * m13 * m2 * m11 -

    m8 * m1 * m14 * m7 -
    m8 * m5 * m2 * m15 -
    m8 * m13 * m6 * m3 -

    m12 * m1 * m6 * m11 -
    m12 * m5 * m10 * m3 -
    m12 * m9 * m2 * m7;

}

void mat4_invert(mat4 result, mat4 m) {
    GLfloat m0 = m[0];
    GLfloat m1 = m[1];
    GLfloat m2 = m[2];
    GLfloat m3 = m[3];
    GLfloat m4 = m[4];
    GLfloat m5 = m[5];
    GLfloat m6 = m[6];
    GLfloat m7 = m[7];
    GLfloat m8 = m[8];
    GLfloat m9 = m[9];
    GLfloat m10 = m[10];
    GLfloat m11 = m[11];
    GLfloat m12 = m[12];
    GLfloat m13 = m[13];
    GLfloat m14 = m[14];
    GLfloat m15 = m[15];

    GLfloat det = mat4_det(m);

    result[0] = (m5  * m10 * m15 -
    m5  * m11 * m14 -
    m9  * m6  * m15 +
    m9  * m7  * m14 +
    m13 * m6  * m11 -
    m13 * m7  * m10) / det;

    result[1] = (-m1  * m10 * m15 +
    m1  * m11 * m14 +
    m9  * m2  * m15 -
    m9  * m3  * m14 -
    m13 * m2  * m11 +
    m13 * m3  * m10) / det;

    result[2] = (m1  * m6 * m15 -
    m1  * m7 * m14 -
    m5  * m2 * m15 +
    m5  * m3 * m14 +
    m13 * m2 * m7  -
    m13 * m3 * m6) / det;

    result[3] = (-m1 * m6 * m11 +
    m1 * m7 * m10 +
    m5 * m2 * m11 -
    m5 * m3 * m10 -
    m9 * m2 * m7  +
    m9 * m3 * m6) / det;

    result[4] = (-m4  * m10 * m15 +
    m4  * m11 * m14 +
    m8  * m6  * m15 -
    m8  * m7  * m14 -
    m12 * m6  * m11 +
    m12 * m7  * m10) / det;

    result[5] = (m0  * m10 * m15 -
    m0  * m11 * m14 -
    m8  * m2 * m15  +
    m8  * m3 * m14  +
    m12 * m2 * m11  -
    m12 * m3 * m10) / det;

    result[6] = (-m0  * m6 * m15 +
    m0  * m7 * m14 +
    m4  * m2 * m15 -
    m4  * m3 * m14 -
    m12 * m2 * m7  +
    m12 * m3 * m6) / det;

    result[7] = (m0 * m6 * m11 -
    m0 * m7 * m10 -
    m4 * m2 * m11 +
    m4 * m3 * m10 +
    m8 * m2 * m7 -
    m8 * m3 * m6) / det;

    result[8] = (m4  * m9  * m15 -
    m4  * m11 * m13 -
    m8  * m5  * m15 +
    m8  * m7  * m13 +
    m12 * m5  * m11 -
    m12 * m7  * m9) / det;

    result[9] = (-m0  * m9  * m15 +
    m0  * m11 * m13 +
    m8  * m1  * m15 -
    m8  * m3  * m13 -
    m12 * m1  * m11 +
    m12 * m3  * m9) / det;

    result[10] = (m0  * m5 * m15 -
    m0  * m7 * m13 -
    m4  * m1 * m15 +
    m4  * m3 * m13 +
    m12 * m1 * m7  -
    m12 * m3 * m5) / det;

    result[11] = (-m0 * m5 * m11 +
    m0 * m7 * m9  +
    m4 * m1 * m11 -
    m4 * m3 * m9  -
    m8 * m1 * m7  +
    m8 * m3 * m5) / det;

    result[12] = (-m4  * m9  * m14 +
    m4  * m10 * m13 +
    m8  * m5  * m14 -
    m8  * m6  * m13 -
    m12 * m5  * m10 +
    m12 * m6  * m9) / det;

    result[13] = (m0  * m9  * m14 -
    m0  * m10 * m13 -
    m8  * m1  * m14 +
    m8  * m2  * m13 +
    m12 * m1  * m10 -
    m12 * m2  * m9) / det;

    result[14] = (-m0  * m5 * m14 +
    m0  * m6 * m13 +
    m4  * m1 * m14 -
    m4  * m2 * m13 -
    m12 * m1 * m6  +
    m12 * m2 * m5) / det;

    result[15] = (m0 * m5 * m10 -
    m0 * m6 * m9  -
    m4 * m1 * m10 +
    m4 * m2 * m9  +
    m8 * m1 * m6  -
    m8 * m2 * m5) / det;
}

void mat4_lookAt(mat4 m, vec3 eye, vec3 at, vec3 up) {
    GLfloat xaxis[3];
    GLfloat yaxis[3];
    GLfloat zaxis[3];

    vec3_sub(zaxis, eye, at);
    vec3_normalize(zaxis);

    vec3_cross(xaxis, up, zaxis);
    vec3_normalize(xaxis);

    vec3_cross(yaxis, zaxis, xaxis);
    vec3_normalize(yaxis);

    m[0]  = xaxis[0];
    m[1]  = yaxis[0];
    m[2]  = zaxis[0];
    m[3]  = 0;

    m[4]  = xaxis[1];
    m[5]  = yaxis[1];
    m[6]  = zaxis[1];
    m[7]  = 0;

    m[8]  = xaxis[2];
    m[9]  = yaxis[2];
    m[10] = zaxis[2];
    m[11] = 0;

    m[12] = -vec3_dot(eye, xaxis);
    m[13] = -vec3_dot(eye, yaxis);
    m[14] = -vec3_dot(eye, zaxis);
    m[15] = 1;
}

void mat4_ortho(mat4 m, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far) {
    m[0]  = 2 / (right - left);
    m[1]  = 0;
    m[2]  = 0;
    m[3]  = 0;

    m[4]  = 0;
    m[5]  = 2 / (top - bottom);
    m[6]  = 0;
    m[7]  = 0;

    m[8]  = 0;
    m[9]  = 0;
    m[10] = -2 / (far - near);
    m[11] = 0;

    m[12] = - (right + left) / (right - left);
    m[13] = - (top + bottom) / (top - bottom);
    m[14] = - (far + near)   / (far - near);
    m[15] = 1;
}

void mat4_perspective(mat4 m, GLfloat yfov, GLfloat aspect, GLfloat near, GLfloat far) {
    GLfloat top = near * tan(yfov / 2);
    GLfloat right = top * aspect;

    m[0]  = near / right;
    m[1]  = 0;
    m[2]  = 0;
    m[3]  = 0;

    m[4]  = 0;
    m[5]  = near / top;
    m[6]  = 0;
    m[7]  = 0;

    m[8]  = 0;
    m[9]  = 0;
    m[10] = -(far + near) / (far - near);
    m[11] = -1;

    m[12] = 0;
    m[13] = 0;
    m[14] = -2 * far * near / (far - near);
    m[15] = 0;
}
