#include "mesh.h"

#include <iostream>

Mesh::Mesh()
{

}

Mesh::Mesh(vector<vec3> positions, vector<vec2> uvs)
{
    positions = positions;
    uvs = uvs;
}

Mesh::Mesh(vector<vec3> positions, vector<unsigned int> indices)
{
    this->positions = positions;
    this->indices = indices;
}

Mesh::Mesh(vector<vec3> positions, vector<vec2> uvs, vector<unsigned int> indices)
{
    positions = positions;
    uvs = uvs;
    indices = indices;
}

Mesh::Mesh(vector<vec3> positions, vector<vec2> uvs, vector<vec3> normals, vector<unsigned int> indices)
{
    positions = positions;
    uvs = uvs;
    normals = normals;
    indices = indices;
}

Mesh::Mesh(vector<vec3> positions, vector<vec2> uvs, vector<vec3> normals, vector<vec3> tangents, vector<vec3> bitangents, vector<unsigned int> indices)
{
    positions = positions;
    uvs = uvs;
    normals = normals;
    tangents = tangents;
    bitangents = bitangents;
    indices = indices;
}

GLuint Mesh::prepare()
{
    // clump data in a single array
    vector<float> data;

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    std::cout << "positions : " << positions.size() << " indices : " << indices.size() << ".\n"; 

    for (int i = 0; i < positions.size(); ++i)
    {
        data.push_back(positions[i][0]);
        data.push_back(positions[i][1]);
        data.push_back(positions[i][2]);
    }

    for (int i = 0; i < uvs.size(); ++i)
    {
        data.push_back(uvs[i][0]);
        data.push_back(uvs[i][1]);
    }
    
    for (int i = 0; i < normals.size(); ++i)
    {
        data.push_back(normals[i][0]);
        data.push_back(normals[i][1]);
        data.push_back(normals[i][2]);
    }

    for (int i = 0; i < tangents.size(); ++i)
    {
        data.push_back(tangents[i][0]);
        data.push_back(tangents[i][1]);
        data.push_back(tangents[i][2]);
    }

    for (int i = 0; i < bitangents.size(); ++i)
    {
        data.push_back(bitangents[i][0]);
        data.push_back(bitangents[i][1]);
        data.push_back(bitangents[i][2]);
    }

    // configure vertex attributes (only on vertex data size() > 0)
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

    // only fill the index buffer if the index array is non-empty.
    if (indices.size() > 0)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    }

    size_t offset = 0;
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
    offset += positions.size() * sizeof(float);
    
    if (uvs.size() > 0)
    {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
        offset += uvs.size() * sizeof(float);
    }

    if (normals.size() > 0)
    {
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
        offset += normals.size() * sizeof(float);
    }

    if (tangents.size() > 0)
    {
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
        offset += tangents.size() * sizeof(float);
    }

    if (bitangents.size() > 0)
    {
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
        offset += bitangents.size() * sizeof(float);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return m_VAO;

}

void Mesh::draw()
{

}
