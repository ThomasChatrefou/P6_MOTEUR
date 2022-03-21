#pragma once

#include "OGLIncludes.hpp"


class Cthulhu
{
public:
	Cthulhu();
	~Cthulhu();

private:
	GLuint _elementBuffer;
	GLuint _vertexArrayID;
	GLuint _uvBuffer;
	GLuint _vertexBuffer;


	GLuint _colorBuffer;

	glm::mat4 _model;

public:
	bool OnInit();
	void OnLoop();
	void OnRender();

public:
	glm::mat4 GetModelMatrix() { return _model; }

	void SetBuffer(
		std::vector<unsigned short> indices,
		std::vector<glm::vec3> vertices,
		std::vector<glm::vec2> uvs,
		std::vector<glm::vec3> normals);
	void SetModelMatrix(glm::mat4 model);
};
