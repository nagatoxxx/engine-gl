#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "../utility/logger.h"
#include "mesh.h"

using namespace eng;

Mesh::Mesh() : m_indices(), m_drawMode(GL_STATIC_DRAW), m_primitiveType(GL_TRIANGLES)
{
}

Mesh::Mesh(const std::string& filepath) : Mesh()
{
    this->loadFromFile(filepath);
}


Mesh::~Mesh()
{
}

void Mesh::setDrawMode(GLenum drawMode, GLenum primitiveType /* = GL_TRIANGLES */)
{
    m_drawMode      = drawMode;
    m_primitiveType = primitiveType;
}

void Mesh::loadFromFile(const std::string& filepath)
{
    Logger::log("Mesh: loading mesh from file: " + filepath);
    Assimp::Importer importer;
    const aiScene*   scene = importer.ReadFile(filepath, aiProcess_Triangulate);

    bool hasNormals = false;
    for (unsigned int m = 0; m < scene->mNumMeshes; m++) {
        aiMesh* mesh = scene->mMeshes[m];

        hasNormals = mesh->HasNormals();

        for (unsigned int v = 0; v < mesh->mNumVertices; v++) {
            Vertex vertex;

            vertex.position.x = mesh->mVertices[v].x;
            vertex.position.y = mesh->mVertices[v].y;
            vertex.position.z = mesh->mVertices[v].z;

            if (hasNormals) {
                vertex.normal.x = mesh->mNormals[v].x;
                vertex.normal.y = mesh->mNormals[v].y;
                vertex.normal.z = mesh->mNormals[v].z;
            }

            m_vertices.push_back(vertex);
        }

        for (unsigned int f = 0; f < mesh->mNumFaces; f++) {
            aiFace& face = mesh->mFaces[f];

            for (unsigned int i = 0; i < face.mNumIndices; i++) {
                m_indices.push_back(face.mIndices[i]);
            }
        }
    }

    if (!hasNormals) {
        this->calculateNormals();
        Logger::log("Mesh: normals calculated successfully");
    }

    m_vbo.bind();
    m_vbo.bufferData(m_vertices.data(), m_vertices.size() * sizeof(Vertex), m_drawMode);

    this->initAttribPointer();

    Logger::log("Mesh: loaded mesh successfully");
}

void Mesh::draw()
{
    m_vao.bind();
    glDrawArrays(m_primitiveType, 0, m_vertices.size());
    m_vao.unbind();
}

/* virtual */ void Mesh::initAttribPointer()
{
    m_vao.bind();

    m_vao.attribPointer(0, 3, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(0));
    m_vao.attribPointer(1, 3, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(sizeof(glm::vec3)));

    m_vao.unbind();
}

void Mesh::calculateNormals()
{
    for (uint64_t i = 0; i < m_vertices.size(); i += 3) {
        glm::vec3 v0 = m_vertices[m_indices[i]].position;
        glm::vec3 v1 = m_vertices[m_indices[i + 1]].position;
        glm::vec3 v2 = m_vertices[m_indices[i + 2]].position;

        m_vertices[m_indices[i]].normal     = glm::normalize(glm::cross(v1 - v0, v2 - v0));
        m_vertices[m_indices[i + 1]].normal = m_vertices[m_indices[i]].normal;
        m_vertices[m_indices[i + 2]].normal = m_vertices[m_indices[i]].normal;
    }
}
