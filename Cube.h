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
		GLfloat g_vertex_buffer_data[108];
		
		mat4 _model;

		GLuint _colorBuffer;
		GLfloat g_color_buffer_data[108];

		GLuint uvbuffer;
		GLuint vertexbuffer;

	public:
		bool OnInit();
		void OnLoop();
		void OnRender();

	public:
		mat4 GetModelMatrix() { return _model; }

		void SetVertex(GLfloat vertexData[108]);

		void SetColor(GLfloat colorData[108]);

		void SetBuffer(
			std::vector<unsigned short> indices,
			std::vector<glm::vec3> vertices,
			std::vector<glm::vec2> uvs,
			std::vector<glm::vec3> normals);
		void SetModelMatrix(mat4 model);
	};
}