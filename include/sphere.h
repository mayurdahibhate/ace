#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "mesh.h"

class Sphere : public Mesh {
    public:
        Sphere(GLuint xSegments=1, GLuint ySegments=1);
};

#endif
