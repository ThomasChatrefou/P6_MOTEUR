#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <vector>
#include <array>
#include <map>

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

	float r, theta, phi, avoidanceGap;
	glm::vec3 m_SphericalCoord;

	int m_nMaxEntities, m_nRenderedEntities, m_nModels;
	std::unique_ptr<Camera> m_Camera;

	//std::multimap<int, int> m_mmapEntities;
	std::vector<int> m_Entities;
	std::vector<glm::mat4> m_MVPs;
	std::vector<std::shared_ptr<Mesh>> m_Meshes;
	std::vector<std::shared_ptr<Material>> m_Materials;
};