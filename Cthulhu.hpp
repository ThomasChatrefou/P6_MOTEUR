#pragma once

#include "OGLIncludes.hpp"


class Cthulhu
{
public:
	Cthulhu();
	~Cthulhu();

private:

	std::vector<unsigned short> m_Indices;
	std::vector<glm::vec3> m_Vertices;
	std::vector<glm::vec2> m_UV;
	std::vector<glm::vec3> m_Normals;

	GLuint m_VertexArrayID;
	GLuint m_VertexBuffer;
	GLuint m_UVBuffer;
	GLuint m_ElementBuffer;

public:
	bool OnInit();
	void OnRender();

public:
	void PrepareForRenderingWithVAO();
};
