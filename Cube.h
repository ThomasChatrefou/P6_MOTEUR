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
		GLuint _vertexArrayID;
		GLuint _vertexBuffer;
		GLfloat g_vertex_buffer_data[108];
		
		mat4 _model;

		GLuint _colorBuffer;
		GLfloat g_color_buffer_data[108];

	public:
		bool OnInit();
		void OnLoop();
		void OnRender();

	public:
		mat4 GetModelMatrix() { return _model; }

		void SetVertex(GLfloat vertexData[108]);

		void SetColor(GLfloat colorData[108]);

		void SetBuffer();
		void SetModelMatrix(mat4 model);
	};
}