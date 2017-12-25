#ifndef __mesh__
#define __mesh__

#include <GL/glew.h>
#include "vec3.h"

namespace mesh {
    typedef struct {
        GLfloat* positions;
        GLfloat* normals;
        GLfloat* uv;
    } mesh;

    struct sphere {
        sphere(GLfloat, GLfloat, GLfloat, GLfloat, int = 10, int = 10);
        GLfloat r;
        vec3::vec3 p;
        mesh arrays;
        int num_vertices;
    };
}

#endif
