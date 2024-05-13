#ifndef _MESH_H_
#define _MESH_H_

// Base Mesh class. A mesh in its simplest form is purely a list of vertices, 
// with some added functionality for easily setting up the hardware configuration relevant for rendering.

#include <GL/glew.h>
#include <GL/gl.h>

#include <vector>
#include "vmath.h"

using std::vector;
using vmath::vec2, vmath::vec3;

class Mesh {

    public:
        GLuint m_VAO = 0;
        GLuint m_VBO = 0;
        GLuint m_EBO = 0;

        // support multiple ways of initializing a mesh
        Mesh();
        Mesh(vector<vec3> positions, vector<vec2> uvs);
        Mesh(vector<vec3> positions, vector<unsigned int> indices);
        Mesh(vector<vec3> positions, vector<vec2> uvs, vector<unsigned int> indices);
        Mesh(vector<vec3> positions, vector<vec2> uvs, vector<vec3> normals, vector<unsigned int> indices);
        Mesh(vector<vec3> positions, vector<vec2> uvs, vector<vec3> normals, vector<vec3> tangents, vector<vec3> bitangents, vector<unsigned int> indices);

        GLuint prepare();
        void draw();

    private:
        vector<vec3> positions = {};
        vector<vec2> uvs = {};
        vector<vec3> normals = {};
        vector<vec3> tangents = {};
        vector<vec3> bitangents = {};

        vector<GLuint> indices = {};
};

#endif