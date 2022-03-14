#include "Cube.h"

namespace GC_3D 
{
	Cube::Cube()
	{
		_vertexArrayID = 0;
		_vertexBuffer = 0;
		_colorBuffer = 0;
		for (int i = 0; i < 108; i++) g_vertex_buffer_data[i] = 0;
		for (int i = 0; i < 108; i++) g_color_buffer_data[i] = 0;
		_model = mat4(1.0f);
	}

	Cube::~Cube()
	{

	}

	bool Cube::OnInit()
	{
		glGenVertexArrays(1, &_vertexArrayID);
		glBindVertexArray(_vertexArrayID);

		return true;
	}

	void Cube::OnLoop()
	{

	}

	void Cube::OnRender()
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
		glVertexAttribPointer(
			0,                  // must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		glDrawArrays(GL_TRIANGLES, 0, 36); // Starting from vertex 0; 3 vertices total
		glDisableVertexAttribArray(0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);
		glVertexAttribPointer(
			1,                  // must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
	}

	void Cube::SetVertex(GLfloat vertexData[108]) 
	{
		for (int i = 0; i < 108; i++) 
		{
			g_vertex_buffer_data[i] = vertexData[i];
		}
	}


	void Cube::SetColor(GLfloat colorData[108]) 
	{
		for (int i = 0; i < 108; i++)
		{
			g_color_buffer_data[i] = colorData[i];
		}
	}
	void Cube::SetBuffer() 
	{
		glGenBuffers(1, &_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

		glGenBuffers(1, &_colorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	}
	
	void Cube::SetModelMatrix(mat4 model)
	{
		_model = model;
	}
}