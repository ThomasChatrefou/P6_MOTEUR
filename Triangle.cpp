#include "Triangle.h"


namespace GC_3D
{
	Triangle::Triangle()
	{
		VertexArrayID = 0;
		vertexbuffer = 0;
		for (int i = 0; i < 9; ++i) g_vertex_buffer_data[i] = 0;
		_model = mat4(1.0f);
	}

	Triangle::~Triangle()
	{

	}

	bool Triangle::OnInit()
	{
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		return true;
	}

	void Triangle::OnLoop()
	{

	}

	void Triangle::OnRender()
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total
		glDisableVertexAttribArray(0);
	}

	void Triangle::SetVertex(GLfloat vertexData[9])
	{
		for (int i = 0; i < 9; ++i) {
			g_vertex_buffer_data[i] = vertexData[i];
		}
	}

	void Triangle::SetVertex(vec3 A, vec3 B, vec3 C)
	{
		for (int i = 0; i < 3; ++i) {
			g_vertex_buffer_data[i] = A[i];
			g_vertex_buffer_data[i + 3] = B[i];
			g_vertex_buffer_data[i + 6] = C[i];
		}
	}

	void Triangle::SetBuffer()
	{
		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	}

	void Triangle::SetModelMatrix(mat4 model)
	{
		_model = model;
	}
}