#include "Camera.hpp"


Camera::Camera()
{
    _fov = 45.0f;
    _ratio = 16.0f / 9.0f;
    _minDisplayDepth = 0.1f;
    _maxDisplayDepth = 100.0f;
    _position = glm::vec3(0.0f);
    _target = glm::vec3(0.0f);
    _upGlobal = glm::vec3(0.0f, 1.0f, 0.0f);
    _forward = glm::vec3(0.0f);
    _right = glm::vec3(0.0f);
    _up = glm::vec3(0.0f);
    _view = glm::mat4(1.0f);
    _projection = glm::mat4(1.0f);
}

Camera::~Camera()
{
}

void Camera::OnInit(glm::vec3& position, glm::vec3& target, float fov, float ratio, float minDisplayDepth, float maxDisplayDepth)
{
    SetPositionAndTarget(position, target);
    SetFrustumParameters(fov, ratio, minDisplayDepth, maxDisplayDepth);
}

void Camera::Update()
{
    _forward = glm::normalize(_target - _position);
    _right = glm::normalize(glm::cross(_upGlobal, -_forward));
    _up = glm::cross(-_forward, _right);
    _view = glm::lookAt(_position, _target, _upGlobal);
}

void Camera::UpdateProjectionMatrix()
{
    _projection = glm::perspective(glm::radians(_fov), _ratio, _minDisplayDepth, _maxDisplayDepth);
}

void Camera::SetFOV(float fov)
{
    _fov = fov;
    UpdateProjectionMatrix();
}

void Camera::SetRatio(float ratio)
{
    _ratio = ratio;
    UpdateProjectionMatrix();
}

void Camera::SetDisplayDepth(float min, float max)
{
    _minDisplayDepth = min;
    _maxDisplayDepth = max;
    UpdateProjectionMatrix();
}

void Camera::SetFrustumParameters(float fov, float ratio, float minDisplayDepth, float maxDisplayDepth)
{
    _fov = fov;
    _ratio = ratio;
    _minDisplayDepth = minDisplayDepth;
    _maxDisplayDepth = maxDisplayDepth;
    UpdateProjectionMatrix();
}

void Camera::SetPosition(glm::vec3& position)
{
    _position = position;
    Update();
}

void Camera::SetTarget(glm::vec3& target)
{
    _target = target;
    Update();
}

void Camera::SetPositionAndTarget(glm::vec3& position, glm::vec3& target)
{
    _position = position;
    _target = target;
    Update();
}