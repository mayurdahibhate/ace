#include "sphere.h"

const float PI    = 3.14159265359;
const float TAU = 6.2831853071;

Sphere::Sphere(GLuint xSegments, GLuint ySegments) {
    
    for (unsigned int y = 0; y <= ySegments; ++y) {
        for (unsigned int x = 0; x <= xSegments; ++x) {
            float xSegment = (float)x / (float)xSegments;
            float ySegment = (float)y / (float)ySegments;
            float xPos = std::cos(xSegment * TAU) * std::sin(ySegment * PI); // TAU is 2PI
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * TAU) * std::sin(ySegment * PI);

            positions.push_back(vec3(xPos, yPos, zPos));
            uvs.push_back(vec2(xSegment, ySegment));
            normals.push_back(vec3(xPos, yPos, zPos));
        }
    }

    for (int y = 0; y < ySegments; ++y) {
        for (int x = 0; x < xSegments; ++x) {
            indices.push_back((y + 1) * (xSegments + 1) + x);
            indices.push_back(y       * (xSegments + 1) + x);
            indices.push_back(y       * (xSegments + 1) + x + 1);

            indices.push_back((y + 1) * (xSegments + 1) + x);
            indices.push_back(y       * (xSegments + 1) + x + 1);
            indices.push_back((y + 1) * (xSegments + 1) + x + 1);
        }
    }
};
