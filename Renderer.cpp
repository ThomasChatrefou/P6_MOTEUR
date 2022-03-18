#pragma once
#include "Renderer.hpp"

void Renderer::CubeRendering(Shader shader, Actor actorToRendering)
{
	
	shader.UseShader();
	shader.LoadAndCreateTexture();
	
}