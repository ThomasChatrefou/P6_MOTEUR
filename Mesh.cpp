#include "Mesh.hpp"	

#include <array>

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "IndexBuffer.hpp"


#ifndef BasicMeshData
#define BasicMeshData
const float CUBE_MESH_DATA[] = {
  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
   0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
   0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
   0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
  -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
   0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
   0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
   0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
   0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
#endif // !BasicMeshData


Mesh::Mesh(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	if (!scene)
	{
		std::cout << "ERROR : Impossible to open file " << path << std::endl;
		return;
	}
	//std::cout << "file open" << std::endl;

	const aiMesh* mesh = scene->mMeshes[0];

	m_VAO = std::make_unique<VertexArray>();

	unsigned int dataCount = 8 * mesh->mNumVertices;
	unsigned int indicesCount = 3 * mesh->mNumFaces;
	unsigned int dim = 3;

	std::vector<float> data(dataCount);
	std::vector<unsigned int> indices(indicesCount);

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D positions = mesh->mVertices[i];
		aiVector3D texCoord = mesh->mTextureCoords[0][i];
		aiVector3D normals = mesh->mNormals[i];

		for (unsigned int j = 0; j < 3; j++) {
			data[8 * i + j] = positions[j];
			data[8 * i + j + 5] = normals[j];
			if (j == 2) break;
			data[8 * i + j + 3] = texCoord[j];
		}
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		for (unsigned int j = 0; j < 3; j++) {
			indices[3 * i + j] = mesh->mFaces[i].mIndices[j];
		}
	}

	BufferMesh({ data.data(), indices.data(), dataCount, indicesCount, 3 });
}

Mesh::Mesh(const MeshData meshData, bool hasUV, bool hasNormals)
{
	BufferMesh(meshData, hasUV, hasNormals);
}

void Mesh::BufferMesh(const MeshData meshData, bool hasUV, bool hasNormals)
{
	m_VAO = std::make_shared<VertexArray>();

	m_VBO = std::make_unique<VertexBuffer>(meshData.data, meshData.dataCount);
	VertexBufferLayout layout;
	layout.Push(meshData.dim);
	if (hasUV)
		layout.Push(2);
	if (hasNormals)
		layout.Push(meshData.dim);

	m_VAO->AddBuffer(*m_VBO, layout);

	m_IndexBuffer = std::make_unique<IndexBuffer>(meshData.indices, meshData.indicesCount);
}

void Mesh::Bind() const
{
	m_VAO->Bind();
	m_IndexBuffer->Bind();
}

void Mesh::Unbind() const
{
	m_VAO->Unbind();
	m_IndexBuffer->Unbind();
}

unsigned int Mesh::getDataCount() const
{ 
	return m_VBO->getCount();
}

unsigned int Mesh::getIndicesCount() const
{ 
	return m_IndexBuffer->getCount();
}