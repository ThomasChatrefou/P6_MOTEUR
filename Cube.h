#pragma once

#include "Includes.hpp"

namespace GC_3D
{
	class Cube
	{
	public:
		Cube();
		~Cube();

	private:
		GLuint _elementBuffer;
		GLuint _vertexArrayID;
		GLuint _uvBuffer;
		GLuint _vertexBuffer;
		

		GLuint _colorBuffer;

		mat4 _model;

	public:
		bool OnInit();
		void OnLoop();
		void OnRender();

	public:
		mat4 GetModelMatrix() { return _model; }

		void SetBuffer(
			std::vector<unsigned short> indices,
			std::vector<glm::vec3> vertices,
			std::vector<glm::vec2> uvs,
			std::vector<glm::vec3> normals);
		void SetModelMatrix(mat4 model);
	};
}