#pragma once
#include "Renderer.hpp"
#include "GetAppPath.hpp"
#include "Shader.hpp"
#include "Actor.hpp"

const char* const TEXTURE_REPOSITORY_NAME = "Sprite";
const char* const TEXTURE_ONE_FILE_NAME = "awesomeface.png";
const char* const TEXTURE_SECOND_FILE_NAME = "container.jpg";
const char* SHADERS_REPOSITORY_NAME = "shaders";
const char* VERTEX_SHADERS_FILE_NAME = "SimpleVertexShader.glsl";
const char* FRAGMENT_SHADERS_FILE_NAME = "SimpleFragmentShader.glsl";

Shader Renderer::CubeRendering()
{

	std::filesystem::path appPath(GetAppPath());
	auto appDir = appPath.parent_path();
	auto textureDirectory = appDir / TEXTURE_REPOSITORY_NAME;
	auto texture1Path = textureDirectory / TEXTURE_ONE_FILE_NAME;
	auto texture2Path = textureDirectory / TEXTURE_SECOND_FILE_NAME;

	std::filesystem::path appPath(GetAppPath());
	auto appDir = appPath.parent_path();
	auto shaderPath = appDir / SHADERS_REPOSITORY_NAME;
	auto vertexShaderPath = shaderPath / VERTEX_SHADERS_FILE_NAME;
	auto fragmentShaderPath = shaderPath / FRAGMENT_SHADERS_FILE_NAME;

	Shader shader = Shader(vertexShaderPath.string().c_str(), fragmentShaderPath.string().c_str());
	shader.LoadAndCreateTexture(texture1Path.string().c_str(), texture2Path.string().c_str());

	return shader;

}

void Renderer::FinalCubeRendering()
{
	Actor actor;
	actor.PrepareCubeToRenderer();
	Shader temp = CubeRendering();
	for (unsigned int i = 0; i < 10; i++)
	{
		actor.LoadMatrix(cubePositions[i], false, 0.0f, i, temp , glm::vec3(1.0f, 1.0f, 1.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	
	

}