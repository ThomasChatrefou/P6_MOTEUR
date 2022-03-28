#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "MyTest.hpp"


class Mesh;
class Material;
class Camera;


class MyTestQuantityGen : public MyTest
{
public:
	MyTestQuantityGen(const AppSystemData& appData);
	~MyTestQuantityGen();

	void OnLoop(float deltaTime) override;
	void OnRender() override;
	void OnGuiRender() override;

private:

	float r, theta, phi;

	int m_NMaxEntities;
	glm::vec3 m_SphericalCoord;
	std::unique_ptr<Camera> m_Camera;

	std::vector<glm::mat4> m_MVPs;

	std::unique_ptr<Mesh> m_Mesh;
	std::unique_ptr<Material> m_Material;
};