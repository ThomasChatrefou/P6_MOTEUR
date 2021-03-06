#pragma once

#include "OGLIncludes.hpp"


class Cthulhu
{
public:
	Cthulhu();
	~Cthulhu();

private:

	std::vector<glm::vec3> m_Vertices;
	std::vector<glm::vec2> m_UV;
	std::vector<glm::vec3> m_Normals;
	std::vector<unsigned short> m_Indices;

	GLuint m_VertexArrayID;
	GLuint m_VertexBuffer;
	GLuint m_UVBuffer;
	GLuint m_ElementBuffer;

public:
	bool OnInit(const char* filePath);
	void OnRender();

public:
	void PrepareForRenderingWithVAO();
};
