#pragma once
#include "OGLIncludes.hpp"
#include "Actor.hpp"
#include "Buffer.hpp"
#include "Mesh.hpp"

void Actor::PrepareCubeToRenderer()
{
	Buffer buffer;
	buffer.CreateBuffer(1, CubeVertices, sizeof(CubeVertices));
	buffer.BindBufferToAttrib(0, 3, 5 * sizeof(float), 0);
	buffer.BindBufferToAttrib(1, 2, 5 * sizeof(float), (3 * sizeof(float)));
}

void Actor::LoadMatrix(glm::vec3 Position, bool rotateShape, float angle, float i, Shader shader, glm::vec3 scale)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, Position) * glm::scale(model,scale);
    if (rotateShape)
    {
        float Rangle = angle * i;
        model = glm::rotate(model, glm::radians(Rangle), glm::vec3(1.0f, 0.3f, 0.5f));
    }

}