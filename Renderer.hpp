#pragma once


class VertexArray;
class IndexBuffer;
class Shader;
class Mesh;
class Material;


class Renderer 
{
private:

public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Draw(const Mesh& mesh, const Material& material) const;

    void EnableBlending();
    void EnableDepthTest();
};