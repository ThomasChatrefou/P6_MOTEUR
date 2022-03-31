#pragma once
#include "OGLIncludes.hpp"


struct VertexBufferElement
{
	unsigned int count;
	unsigned int type;
	unsigned char normalized;
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;

public:
	VertexBufferLayout() : m_Stride(0) {}

	void PushVertex()
	{
		Push(3);
		Push(2);
		Push(3);
		Push(1);
	}

	void Push(unsigned int count) 
	{
		VertexBufferElement vbe = {count, GL_FLOAT, GL_FALSE };
		m_Elements.push_back(vbe);
		m_Stride += count * sizeof(GLfloat);
	}

	inline const std::vector<VertexBufferElement> getElements() const& { return m_Elements; }
	inline unsigned int getStride() const { return m_Stride; }
};