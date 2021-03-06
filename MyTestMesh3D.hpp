#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "MyTest.hpp"


class Mesh;
class Material;
class Camera;


class MyTestMesh3D : public MyTest
{
public:
	MyTestMesh3D(const AppSystemData& appData);
	~MyTestMesh3D();

	void OnLoop(float deltaTime) override;
	void OnRender() override;
	void OnGuiRender() override;

private:
	glm::vec3 m_Translation;
	glm::vec3 m_Rotation;
	glm::mat4 m_Proj;
	glm::mat4 m_View;

	std::unique_ptr<Mesh> m_Mesh;
	std::unique_ptr<Material> m_Material;
	std::unique_ptr<Camera> m_Camera;
};