#ifndef __QUAT__
#define __QUAT__

#include <GL/glew.h>
#include "mat4.h"

namespace quat {
    typedef GLfloat quat[4];
    void set(quat, GLfloat, GLfloat, GLfloat, GLfloat);
    GLfloat dot(quat, quat);
    GLfloat length(quat);
    void normalize(quat);
    void mult(quat, quat, quat);
    void matrix(mat4::mat4, quat);
    void slerp(quat, quat, quat, GLfloat);
}

#endif
