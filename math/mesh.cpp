#include <GL/glew.h>
#include <math.h>
#include "vec3.h"
#include "mesh.h"

mesh::sphere::sphere(GLfloat x, GLfloat y, GLfloat z, GLfloat r, int long_bands, int lat_bands) {
    GLfloat lat_step = M_PI / lat_bands;
    GLfloat long_step = 2 * M_PI / long_bands;
    int num_vertices = long_bands * lat_bands * 6;
    GLfloat lat_angle, long_angle;
    GLfloat* positions = new GLfloat[num_vertices * 3];
    GLfloat* normals = new GLfloat[num_vertices * 3];
    GLfloat* uv = new GLfloat[num_vertices * 2];
    GLfloat ox = x;
    GLfloat oy = y;
    GLfloat oz = z;
    GLfloat x1, x2, x3, x4,
        y1, y2,
        z1, z2, z3, z4,
        u1, u2,
        v1, v2;
    int k = 0;
    int vi, ti;

    for (int i = 0; i < lat_bands; i++) {
        lat_angle = i * lat_step;
        y1 = cos(lat_angle);
        y2 = cos(lat_angle + lat_step);
        for (int j = 0; j < long_bands; j++) {
            long_angle = j * long_step;
            x1 = sin(lat_angle) * cos(long_angle);
            x2 = sin(lat_angle) * cos(long_angle + long_step);
            x3 = sin(lat_angle + lat_step) * cos(long_angle);
            x4 = sin(lat_angle + lat_step) * cos(long_angle + long_step);
            z1 = sin(lat_angle) * sin(long_angle);
            z2 = sin(lat_angle) * sin(long_angle + long_step);
            z3 = sin(lat_angle + lat_step) * sin(long_angle);
            z4 = sin(lat_angle + lat_step) * sin(long_angle + long_step);
            u1 = 1 - (float)j / long_bands;
            u2 = 1 - (float)(j + 1) / long_bands;
            v1 = 1 - (float)i / lat_bands;
            v2 = 1 - (float)(i + 1) / lat_bands;
            vi = k * 3;
            ti = k * 2;

            positions[vi] = x1 * r + ox;
            positions[vi+1] = y1 * r + oy;
            positions[vi+2] = z1 * r + oz;
            positions[vi+3] = x2 * r + ox;
            positions[vi+4] = y1 * r + oy;
            positions[vi+5] = z2 * r + oz;
            positions[vi+6] = x3 * r + ox;
            positions[vi+7] = y2 * r + oy;
            positions[vi+8] = z3 * r + oz;
            positions[vi+9] = x3 * r + ox;
            positions[vi+10] = y2 * r + oy;
            positions[vi+11] = z3 * r + oz;
            positions[vi+15] = x4 * r + ox;
            positions[vi+16] = y2 * r + oy;
            positions[vi+17] = z4 * r + oz;
            positions[vi+12] = x2 * r + ox;
            positions[vi+13] = y1 * r + oy;
            positions[vi+14] = z2 * r + oz;

            normals[vi] = x1;
            normals[vi+1] = y1;
            normals[vi+2] = z1;
            normals[vi+3] = x2;
            normals[vi+4] = y1;
            normals[vi+5] = z2;
            normals[vi+6] = x3;
            normals[vi+7] = y2;
            normals[vi+8] = z3;
            normals[vi+9] = x3;
            normals[vi+10] = y2;
            normals[vi+11] = z3;
            normals[vi+12] = x2;
            normals[vi+13] = y1;
            normals[vi+14] = z2;
            normals[vi+15] = x4;
            normals[vi+16] = y2;
            normals[vi+17] = z4;

            uv[ti] = u1;
            uv[ti+1] = v1;
            uv[ti+2] = u2;
            uv[ti+3] = v1;
            uv[ti+4] = u1;
            uv[ti+5] = v2;
            uv[ti+6] = u1;
            uv[ti+7] = v2;
            uv[ti+8] = u2;
            uv[ti+9] = v1;
            uv[ti+10] = u2;
            uv[ti+11] = v2;

            k += 6;
        }
    }

    this->r = r;
    this->num_vertices = num_vertices;
    vec3::set(this->p, x, y, z);
    this->arrays.positions = positions;
    this->arrays.normals = normals;
    this->arrays.uv = uv;
}
