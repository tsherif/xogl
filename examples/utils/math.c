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

#include <math.h>
#include "math.h"

static vec3 tempVec3;
static mat4 tempMat4;

void math_setVec3(vec3 v, float x, float y, float z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

float math_dotVec3(vec3 v1, vec3 v2) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

float math_lengthVec3(vec3 v) {
    return sqrt(math_dotVec3(v, v));
}

void math_scaleVec3(vec3 v, float s) {
    v[0] *= s;
    v[1] *= s;
    v[2] *= s;
}

void math_normalizeVec3(vec3 v) {
    float l = math_lengthVec3(v);
    v[0] /= l;
    v[1] /= l;
    v[2] /= l;
}

void math_addVec3(vec3 out, vec3 v1, vec3 v2) {
    out[0] = v1[0] + v2[0];
    out[1] = v1[1] + v2[1];
    out[2] = v1[2] + v2[2];
}

void math_subVec3(vec3 out, vec3 v1, vec3 v2) {
    out[0] = v1[0] - v2[0];
    out[1] = v1[1] - v2[1];
    out[2] = v1[2] - v2[2];
}

void math_crossVec3(vec3 out, vec3 v1, vec3 v2) {
    tempVec3[0] = v1[1] * v2[2] - v1[2] * v2[1];
    tempVec3[1] = v1[2] * v2[0] - v1[0] * v2[2];
    tempVec3[2] = v1[0] * v2[1] - v1[1] * v2[0];

    out[0] = tempVec3[0];
    out[1] = tempVec3[1];
    out[2] = tempVec3[2];
}

void math_identityMat4(mat4 m) {
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

void math_translationMat4(mat4 m, float x, float y, float z) {
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

void math_scalingMat4(mat4 m, float x, float y, float z) {
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

void math_rotationXMat4(mat4 m, float theta) {
    float sine = sin(theta);
    float cosine = cos(theta);

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

void math_rotationYMat4(mat4 m, float theta) {
    float sine = sin(theta);
    float cosine = cos(theta);

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

void math_rotationZMat4(mat4 m, float theta) {
    float sine = sin(theta);
    float cosine = cos(theta);

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

void math_multiplyMat4(mat4 result, mat4 m1, mat4 m2) {
    int row, col, i;
    int result_index, m1_index, m2_index;
    float val;

    for (col = 0; col < 4; col++) {
        for (row = 0; row < 4; row++) {
            result_index = col * 4 + row;
            val = 0;

            for (i = 0; i < 4; i++) {
                m1_index = i   * 4 + row;
                m2_index = col * 4 + i;

                val += m1[m1_index] * m2[m2_index];
            }

            tempMat4[result_index] = val;
        }
    }

    for (i = 0; i < 16; i++) {
        result[i] = tempMat4[i];
    }
}

void math_mat4TransformVec3(vec3 out, mat4 m, vec3 v) {
    tempVec3[0] = v[0] * m[0] + v[1] * m[4] + v[2] * m[8]  + m[12];
    tempVec3[1] = v[0] * m[1] + v[1] * m[5] + v[2] * m[9]  + m[13];
    tempVec3[2] = v[0] * m[2] + v[1] * m[6] + v[2] * m[10] + m[14];

    out[0] = tempVec3[0];
    out[1] = tempVec3[1];
    out[2] = tempVec3[2];
}

void math_transposeMat4(mat4 result, mat4 m) {
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

float math_detMat4(mat4 m) {
    float m0 = m[0];
    float m1 = m[1];
    float m2 = m[2];
    float m3 = m[3];
    float m4 = m[4];
    float m5 = m[5];
    float m6 = m[6];
    float m7 = m[7];
    float m8 = m[8];
    float m9 = m[9];
    float m10 = m[10];
    float m11 = m[11];
    float m12 = m[12];
    float m13 = m[13];
    float m14 = m[14];
    float m15 = m[15];

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

void math_invertMat4(mat4 result, mat4 m) {
    float m0 = m[0];
    float m1 = m[1];
    float m2 = m[2];
    float m3 = m[3];
    float m4 = m[4];
    float m5 = m[5];
    float m6 = m[6];
    float m7 = m[7];
    float m8 = m[8];
    float m9 = m[9];
    float m10 = m[10];
    float m11 = m[11];
    float m12 = m[12];
    float m13 = m[13];
    float m14 = m[14];
    float m15 = m[15];

    float det = math_detMat4(m);

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

void math_lookAtMat4(mat4 m, vec3 eye, vec3 at, vec3 up) {
    float xaxis[3];
    float yaxis[3];
    float zaxis[3];

    math_subVec3(zaxis, eye, at);
    math_normalizeVec3(zaxis);

    math_crossVec3(xaxis, up, zaxis);
    math_normalizeVec3(xaxis);

    math_crossVec3(yaxis, zaxis, xaxis);
    math_normalizeVec3(yaxis);

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

    m[12] = -math_dotVec3(eye, xaxis);
    m[13] = -math_dotVec3(eye, yaxis);
    m[14] = -math_dotVec3(eye, zaxis);
    m[15] = 1;
}

void math_orthoMat4(mat4 m, float left, float right, float bottom, float top, float near, float far) {
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

void math_perspectiveMat4(mat4 m, float yfov, float aspect, float near, float far) {
    float top = near * tan(yfov / 2);
    float right = top * aspect;

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
