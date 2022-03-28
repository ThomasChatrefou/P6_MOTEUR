#pragma once


class VertexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;

public:
	VertexBuffer(const float* data, unsigned int count);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int getCount() const { return m_Count; }
};


