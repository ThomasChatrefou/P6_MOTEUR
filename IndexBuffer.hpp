#pragma once
#include "OGLIncludes.hpp"


class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;

public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int getCount() const { return m_Count; }

	/*
public:
	Buffer() {}
	~Buffer() {}

public:
	unsigned int VAO, VBO;

private:
	GLuint m_Buffer;
	GLuint m_ElementBuffer;
	std::vector<unsigned int> m_Indices;

public:
	void CreateBuffer(int size, const GLfloat* iData, size_t iSize);
	void BindBufferToAttrib(int attribut, int size, int stride, int arrayOffset);
	void Vao();
	*/
};


