#include "Cube.h"
#include "GetAppPath.h"
#include "LoadModel.h"

#include <filesystem>

namespace GC_3D 
{
		

	Cube::Cube()
	{

		_vertexArrayID = 0;
		_vertexBuffer = 0;
		_elementBuffer = 0;
		_uvBuffer = 0;
		_colorBuffer = 0;
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
		std::filesystem::path appPath(GetAppPath());
		auto const appDir = appPath.parent_path();
		auto const modelPath = appDir / "resources" / "FBX" / "Cthulhu.fbx";

		std::vector<unsigned short> indices;
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;

		Importer::DoTheImportThing(modelPath.string().c_str(), indices, vertices, uvs, normals);

		SetBuffer(indices, vertices, uvs, normals);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer); // bind to the next VertexAttribPointer
		glVertexAttribPointer(
			0,                  // must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer); // bind to the next VertexAttribPointer
		glVertexAttribPointer(
			1,                  // must match the layout in the shader.
			2,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);

		glDrawElements(
			GL_TRIANGLES,
			indices.size(),
			GL_UNSIGNED_SHORT,
			(void*)0
		);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}

	void Cube::SetBuffer(std::vector<unsigned short> indices,
	std::vector<glm::vec3> vertices,
	std::vector<glm::vec2> uvs,
	std::vector<glm::vec3> normals)
	{
		
		glGenBuffers(1, &_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
		
		glGenBuffers(1, &_elementBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);
		
		glGenBuffers(1, &_uvBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), uvs.data(), GL_STATIC_DRAW);
	}
	
	void Cube::SetModelMatrix(mat4 model)
	{
		_model = model;
	}
}