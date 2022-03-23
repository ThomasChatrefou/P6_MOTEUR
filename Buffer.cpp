#pragma once
#include "Buffer.hpp"

void Buffer::CreateBuffer(int size, const GLfloat* iData, size_t iSize)
{
	glGenBuffers(1, &m_Buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
	glBufferData(GL_ARRAY_BUFFER, iSize, iData, GL_STATIC_DRAW);
}

void Buffer::BindBufferToAttrib(int attribut, int size, int stride, int arrayOffset)
{
    // 1rst attribute buffer : vertices
    glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
    glEnableVertexAttribArray(attribut);
    glVertexAttribPointer(attribut, size, GL_FLOAT, GL_FALSE, stride, (void*)arrayOffset);
}

void Buffer::Vao()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
}
