#pragma once
#include "OGLIncludes.hpp"
#include "Shader.hpp"
#include "Actor.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();
	void CubeRendering(Shader shader, Actor actorToRenderer);
private:

};

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}
