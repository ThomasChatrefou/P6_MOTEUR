#pragma once
#include "Mesh.hpp"	

bool Mesh::LoadMesh(const std::string& pFile)
{
	// Create an instance of the Importer class
	Assimp::Importer importer;

	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll 
	// propably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(pFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (!scene)
	{
		//std::cout << "file couldn't open" << std::endl;
		std::cout << "error : file can't open" << std::endl;
		return false;
	}
	// We're done. Everything will be cleaned up by the importer destructor
	//std::cout << "file could open" << std::endl;
	std::cout << "file open" << std::endl;


	const aiMesh* mesh = scene->mMeshes[0]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)

	// Fill vertices positions
	m_Vertices.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D pos = mesh->mVertices[i];
		m_Vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
	}

	// Fill vertices texture coordinates
	m_UV.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
		m_UV.push_back(glm::vec2(UVW.x, UVW.y));
	}

	// Fill vertices normals
	m_Normals.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D n = mesh->mNormals[i];
		m_Normals.push_back(glm::vec3(n.x, n.y, n.z));
	}


	// Fill face indices
	m_Indices.reserve(3 * mesh->mNumFaces);
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		// Assume the model has only triangles.
		m_Indices.push_back(mesh->mFaces[i].mIndices[0]);
		m_Indices.push_back(mesh->mFaces[i].mIndices[1]);
		m_Indices.push_back(mesh->mFaces[i].mIndices[2]);
	}
	return true;
}