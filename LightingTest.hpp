#pragma once
#include "OGLIncludes.hpp"
#include "MyTest.hpp"
#include <memory>
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Material.hpp"

class LightingTest : public MyTest
{
public:
	LightingTest(const AppSystemData& appData);
	~LightingTest();

	void OnLoop(float deltaTime) override;
	void OnRender() override;
	void OnGuiRender() override;

private:
	glm::vec3 lightPos;

	glm::vec3 m_Translation;
	glm::vec3 m_Rotation;
	glm::mat4 m_Proj;
	glm::mat4 m_View;

	float ambientStrength;
	float specularStrength;
	int specularPower;



	std::unique_ptr<Camera> m_Camera;
	std::shared_ptr<Mesh> m_CurrentMesh;
	std::shared_ptr<Material> m_CurrentMaterial;

	std::vector<std::shared_ptr<Mesh>> m_Meshes;
	std::vector<std::shared_ptr<Material>> m_Materials;

public:

};