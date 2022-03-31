#pragma once

#include "OGLIncludes.hpp"


class MyTexture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public:
	MyTexture(const std::string& path);
	~MyTexture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int getWidth() const { return m_Width; }
	inline int getHeight() const { return m_Height; }
	inline unsigned int getID() const { return m_RendererID; }
};