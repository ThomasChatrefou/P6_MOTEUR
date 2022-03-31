#pragma once
#include "OGLIncludes.hpp"

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"


struct MeshData
{
    float* data;
    unsigned int* indices;
    unsigned int dataCount;
    unsigned int indicesCount;
    unsigned int dim;
};


class Mesh
{
public:
    Mesh(const std::string& pFile);
    Mesh(const MeshData meshData, bool hasUV = true, bool hasNormals = true);

    void BufferMesh(const MeshData meshData, bool hasUV = true, bool hasNormals = true);

    void Bind() const;
    void Unbind() const;

    unsigned int getDataCount() const;
    unsigned int getIndicesCount() const;
    inline std::shared_ptr<VertexArray> getVAO() const { return m_VAO; }
    inline std::shared_ptr<IndexBuffer> getIndexBuffer() const { return m_IndexBuffer; }

private:
    std::shared_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;

};