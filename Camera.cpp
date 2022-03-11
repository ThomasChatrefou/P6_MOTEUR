#include "Camera.h"


namespace GC_3D
{
    Camera::Camera()
    {
        _fov = 45.0f;
        _ratio = 16.0f / 9.0f;
        _minDisplayDepth = 0.1f;
        _maxDisplayDepth = 100.0f;
        _position = vec3(0.0f);
        _target = vec3(0.0f);
        _upGlobal = vec3(0.0f, 1.0f, 0.0f);
        _forward = vec3(0.0f);
        _right = vec3(0.0f);
        _up = vec3(0.0f);
        _view = mat4(1.0f);
        _projection = mat4(1.0f);
    }

    Camera::~Camera() 
    {

    }

    void Camera::OnInit(vec3 &position, vec3 &target, float fov, float ratio, float minDisplayDepth, float maxDisplayDepth)
    {
        SetPositionAndTarget(position, target);
        SetFrustumParameters(fov, ratio, minDisplayDepth, maxDisplayDepth);
    }

    void Camera::Update()
    {
        _forward = normalize(_target - _position);
        _right = normalize(glm::cross(_upGlobal, -_forward));
        _up = cross(-_forward, _right);
        _view = lookAt(_position, _target, _upGlobal);
    }

    void Camera::UpdateProjectionMatrix()
    {
        _projection = perspective(radians(_fov), _ratio, _minDisplayDepth, _maxDisplayDepth);
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

    void Camera::SetPosition(vec3 &position)
    {
        _position = position;
        Update();
    }

    void Camera::SetTarget(vec3 &target)
    {
        _target = target;
        Update();
    }
    
    void Camera::SetPositionAndTarget(vec3 &position, vec3 &target)
    {
        _position = position;
        _target = target;
        Update();
    }
}