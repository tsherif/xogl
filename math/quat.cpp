#include <math.h>
#include "math.h"
#include "quat.h"

void quat::set(quat::quat q, GLfloat theta, GLfloat x, GLfloat y, GLfloat z) {
    GLfloat half_theta = theta * 0.5;
    q[0] = cos(half_theta);
    q[1] = sin(half_theta) * x;
    q[2] = sin(half_theta) * y;
    q[3] = sin(half_theta) * z;
}

GLfloat quat::dot(quat::quat q1, quat::quat q2) {
    return q1[0] * q2[0] + q1[1] * q2[1] + q1[2] * q2[2] + q1[3] * q2[3];
}

GLfloat quat::length(quat::quat q) {
    return sqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
}

void quat::normalize(quat::quat q) {
    GLfloat l = quat::length(q);

    q[0] /= l;
    q[1] /= l;
    q[2] /= l;
    q[3] /= l;
}

void quat::mult(quat::quat result, quat::quat q1, quat::quat q2) {
    result[0] = q2[0] * q1[0] - q2[1] * q1[1] - q2[2] * q1[2] - q2[3] * q1[3];
    result[1] = q2[0] * q1[1] + q2[1] * q1[0] - q2[2] * q1[3] + q2[3] * q1[2];
    result[2] = q2[0] * q1[2] + q2[1] * q1[3] + q2[2] * q1[0] - q2[3] * q1[1];
    result[3] = q2[0] * q1[3] - q2[1] * q1[2] + q2[2] * q1[1] + q2[3] * q1[0];
}

void quat::matrix(mat4::mat4 m, quat::quat q) {
    GLfloat w = q[0];
    GLfloat x = q[1];
    GLfloat y = q[2];
    GLfloat z = q[3];

    m[0]  = 1 - 2 * y * y - 2 * z * z;
    m[1]  = 2 * x * y + 2 * w * z;
    m[2]  = 2 * x * z - 2 * w * y;
    m[3]  = 0;

    m[4]  = 2 * x * y - 2 * w * z;
    m[5]  = 1 - 2 * x * x - 2 * z * z;
    m[6]  = 2 * y * z + 2 * w * x;
    m[7]  = 0;

    m[8]  = 2 * x * z + 2 * w * y;
    m[9]  = 2 * y * z - 2 * w * x;
    m[10] = 1 - 2 * x * x - 2 * y * y;
    m[11] = 0;

    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
}

void quat::slerp(quat result, quat q1, quat q2, GLfloat t) {
    GLfloat dp = quat::dot(q1, q2);

    if (fabs(dp) >= 1.0f) {
        result[0] = q1[0];
        result[1] = q1[1];
        result[2] = q1[2];
        result[3] = q1[3];

        return;
    }

    GLfloat sin_omega = sqrt(1.0f - dp * dp);

    if (fabs(sin_omega) < 0.001f) {
        result[0] = (1.0f - t) * q1[0] + t * q2[0];
        result[1] = (1.0f - t) * q1[1] + t * q2[1];
        result[2] = (1.0f - t) * q1[2] + t * q2[2];
        result[3] = (1.0f - t) * q1[3] + t * q2[3];

        return;
    }

    GLfloat omega = acos(dp);
    GLfloat a = sin((1.0f - t) * omega) / sin_omega;
    GLfloat b = sin(t * omega) / sin_omega;

    result[0] = a * q1[0] + b * q2[0];
    result[1] = a * q1[1] + b * q2[1];
    result[2] = a * q1[2] + b * q2[2];
    result[3] = a * q1[3] + b * q2[3];
}
