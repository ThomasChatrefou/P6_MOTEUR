#ifdef _WIN32
#include <windows.h>
#endif 

#include <iostream>
#include <gl/GL.h>
#include <SDL.h>

#include "Camera.h"


namespace GC_3D
{
    Camera::Camera(vec3 position, vec3 target)
    {
        _position = position;
        _target = target;
        _upGlobal = vec3(0.0f, 1.0f, 0.0f);

        _forward = glm::normalize(_target - _position);
        _right = glm::normalize(glm::cross(_upGlobal, -_forward));
        _up = glm::cross(-_forward, _right);

        _view = lookAt(_position, _target, _upGlobal);
    }

    Camera::~Camera() 
    {

    }

    void Camera::Update(vec3 position, vec3 target) 
    {
        _position = position;
        _target = target;

        _forward = glm::normalize(_target - _position);
        _right = glm::normalize(glm::cross(_upGlobal, -_forward));
        _up = glm::cross(-_forward, _right);

        _view = lookAt(_position, _target, _upGlobal);
    }
}