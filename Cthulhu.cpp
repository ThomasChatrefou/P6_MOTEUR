#include "Cthulhu.hpp"
#include "GetAppPath.hpp"
#include "Importer.hpp"


Cthulhu::Cthulhu()
{
	m_VertexArrayID = 0;
	m_VertexBuffer = 0;
	m_ElementBuffer = 0;
	m_UVBuffer = 0;
}

Cthulhu::~Cthulhu()
{

}

bool Cthulhu::OnInit(const char* filePath)
{
	std::filesystem::path appPath(GetAppPath());
	auto const appDir = appPath.parent_path();
	auto const modelPath = appDir / filePath;
	Importer::DoTheImportThing(modelPath.string().c_str(), m_Indices, m_Vertices, m_UV, m_Normals);

	PrepareForRenderingWithVAO();
	return true;
}

void Cthulhu::OnRender()
{
	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_SHORT, (void*)0);
}

void Cthulhu::PrepareForRenderingWithVAO()
{
	glGenVertexArrays(1, &m_VertexArrayID);
	glBindVertexArray(m_VertexArrayID);

	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(glm::vec3), m_Vertices.data(), GL_STATIC_DRAW);

	int positionLocation = 0;
	glEnableVertexAttribArray(positionLocation);
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glGenBuffers(1, &m_UVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_UVBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_UV.size() * sizeof(glm::vec2), m_UV.data(), GL_STATIC_DRAW);

	int TextureCoordinatesLocation = 1;
	glEnableVertexAttribArray(TextureCoordinatesLocation);
	glVertexAttribPointer(TextureCoordinatesLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glGenBuffers(1, &m_ElementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned short), m_Indices.data(), GL_STATIC_DRAW);
}