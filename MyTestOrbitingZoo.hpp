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


struct Entity
{
	int modelID;
	float aspeed;
	glm::vec3 sphericalCoord;
};


class MyTestOrbitingZoo : public MyTest
{
public:
	MyTestOrbitingZoo(const AppSystemData& appData);
	~MyTestOrbitingZoo();

	void OnLoop(float deltaTime) override;
	void OnRender() override;
	void OnGuiRender() override;

private:

	float r, thetaMax, phi, aspeed;
	float rAmp, phiAmp, aspeedAmp;

	glm::mat4 m_Proj;
	glm::mat4 m_View;

	int m_nMaxEntities, m_nRenderedEntities, m_nModels;
	std::unique_ptr<Camera> m_Camera;

	//std::multimap<int, int> m_mmapEntities;
	std::vector<Entity> m_Entities;
	std::vector<std::shared_ptr<Mesh>> m_Meshes;
	std::vector<std::shared_ptr<Material>> m_Materials;
};