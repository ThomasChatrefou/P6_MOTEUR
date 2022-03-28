#pragma once
#include "OGLIncludes.hpp"

class Buffer
{
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
	void CreateBuffer(const GLfloat* iData, size_t iSize);
	void BindBufferToAttrib(int attribut, int size, int stride, int arrayOffset);
	void Vao();
	
};


