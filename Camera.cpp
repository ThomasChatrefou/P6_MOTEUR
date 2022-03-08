#ifdef _WIN32
#include <windows.h>
#endif 

#include <iostream>
#include <gl/GL.h>
#include <SDL.h>

#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 target)
{
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    _forward = glm::normalize(_position - target);
    _right = glm::normalize(glm::cross(up, _forward));
    _up = glm::cross(_forward, _right);
}
