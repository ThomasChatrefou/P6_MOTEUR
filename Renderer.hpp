#pragma once
#include "OGLIncludes.hpp"
#include "Shader.hpp"
#include "Actor.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();
	Shader CubeRendering();
	void FinalCubeRendering();
private:

};

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

static const glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f, 0.0f),
        glm::vec3(2.0f,  0.0f, 0.0f),
        glm::vec3(4.0f,  0.0f, 0.0f),
        glm::vec3(6.0f,  0.0f, 0.0f),
        glm::vec3(8.0f,  0.0f, 0.0f),
        glm::vec3(10.0f, 0.0f, 0.0f),
        glm::vec3(12.0f, 0.0f, 0.0f),
        glm::vec3(14.0f, 0.0f, 0.0f),
        glm::vec3(16.0f, 0.0f, 0.0f),
        glm::vec3(18.0f, 0.0f, 0.0f),
        glm::vec3(20.0f, 0.0f, 0.0f)
};