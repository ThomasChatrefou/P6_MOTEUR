#pragma once

#include "Includes.hpp"

namespace GC_3D
{
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

		vec3 _position;
		vec3 _target;
		vec3 _upGlobal;
		vec3 _forward;
		vec3 _right;
		vec3 _up;

		mat4 _view;
		mat4 _projection;

	public:
		void OnInit(vec3&, vec3&, float, float, float, float);
		void Update();
		void UpdateProjectionMatrix();

	public:
		vec3 GetPosition() { return _position; }
		vec3 GetTarget() { return _target; }
		vec3 GetForwardVector() { return _forward; }
		vec3 GetRightVector() { return _right; }
		vec3 GetUpVector() { return _up; }
		mat4 GetLookAtMatrix() { return _view; }
		mat4 GetProjectionMatrix() { return _projection; }

		void SetFOV(float);
		void SetRatio(float);
		void SetDisplayDepth(float, float);
		void SetFrustumParameters(float, float, float, float);
		void SetPosition(vec3&);
		void SetTarget(vec3&);
		void SetPositionAndTarget(vec3&, vec3&);
	};
}