#pragma once

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec3 Normals;
	float TexID;
};


class VertexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;

public:
	VertexBuffer(unsigned int count);
	VertexBuffer(const float* data, unsigned int count);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int getID() const { return m_RendererID; }
	inline unsigned int getCount() const { return m_Count; }
};


