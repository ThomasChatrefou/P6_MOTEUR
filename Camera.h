#pragma once

#include"gc_3d_defs.hpp"

namespace GC_3D
{
	class Camera
	{
	public:
		Camera::Camera(vec3 position, vec3 target);
		~Camera();

		void Camera::Update(vec3 position, vec3 target);

		vec3 GetPosition() { return _position; }
		vec3 GetTarget() { return _target; }

		vec3 GetForwardVector() { return _forward; }
		vec3 GetRightVector() { return _right; }
		vec3 GetUpVector() { return _up; }

		mat4 GetLookAtMatrix() { return _view; }

	private:
		vec3 _position;
		vec3 _target;
		vec3 _upGlobal;

		vec3 _forward;
		vec3 _right;
		vec3 _up;

		mat4 _view;
	};
}