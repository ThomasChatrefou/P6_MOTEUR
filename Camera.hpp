#pragma once

#include "OGLIncludes.hpp"


class Camera
{
public:
	Camera::Camera();
	~Camera();

private:
	float _fov;
	float _ratio;
	float _minDisplayDepth;
	float _maxDisplayDepth;

	glm::vec3 _position;
	glm::vec3 _target;
	glm::vec3 _upGlobal;
	glm::vec3 _forward;
	glm::vec3 _right;
	glm::vec3 _up;

	glm::mat4 _view;
	glm::mat4 _projection;

public:
	void OnInit(glm::vec3&, glm::vec3&, float, float, float, float);
	void Update();
	void UpdateProjectionMatrix();

public:
	glm::vec3 GetPosition() { return _position; }
	glm::vec3 GetTarget() { return _target; }
	glm::vec3 GetForwardVector() { return _forward; }
	glm::vec3 GetRightVector() { return _right; }
	glm::vec3 GetUpVector() { return _up; }
	glm::mat4 GetLookAtMatrix() { return _view; }
	glm::mat4 GetProjectionMatrix() { return _projection; }

	void SetFOV(float);
	void SetRatio(float);
	void SetDisplayDepth(float, float);
	void SetFrustumParameters(float, float, float, float);
	void SetPosition(glm::vec3&);
	void SetTarget(glm::vec3&);
	void SetPositionAndTarget(glm::vec3&, glm::vec3&);
};