#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera::Camera(glm::vec3 position, glm::vec3 target);

private:
	glm::vec3 _position;
	glm::vec3 _forward;
	glm::vec3 _right;
	glm::vec3 _up;
};