#include "Triangle.h"


namespace GC_3D
{
	Triangle::Triangle()
	{
		_vertexArrayID = 0;
		_vertexBuffer = 0;
		for (int i = 0; i < 9; ++i) _vertexBufferData[i] = 0;
		_model = mat4(1.0f);
	}

	Triangle::~Triangle()
	{

	}

	bool Triangle::OnInit()
	{
		glGenVertexArrays(1, &_vertexArrayID);
		glBindVertexArray(_vertexArrayID);

		return true;
	}

	void Triangle::OnLoop()
	{

	}

	void Triangle::OnRender()
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
		glVertexAttribPointer(
			0,                  // must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);
		glVertexAttribPointer(
			1,                                // must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}

	void Triangle::SetVertex(GLfloat vertexData[9])
	{
		for (int i = 0; i < 9; ++i) {
			_vertexBufferData[i] = vertexData[i];
		}
	}

	void Triangle::SetVertex(vec3 A, vec3 B, vec3 C)
	{
		for (int i = 0; i < 3; ++i) {
			_vertexBufferData[i] = A[i];
			_vertexBufferData[i + 3] = B[i];
			_vertexBufferData[i + 6] = C[i];
		}
	}

	void Triangle::SetColor(GLfloat colorData[9])
	{
		for (int i = 0; i < 9; ++i) {
			_colorBufferData[i] = colorData[i];
		}
	}

	void Triangle::SetBuffer()
	{
		glGenBuffers(1, &_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(_vertexBufferData), _vertexBufferData, GL_STATIC_DRAW);
		
		glGenBuffers(1, &_colorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(_colorBufferData), _colorBufferData, GL_STATIC_DRAW);
		
	}

	void Triangle::SetModelMatrix(mat4 model)
	{
		_model = model;
	}
}