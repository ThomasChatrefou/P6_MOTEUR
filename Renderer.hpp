#pragma once

class VertexArray;
class IndexBuffer;
class Shader;


class Renderer 
{
private:

public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};