#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <vector>
#include <array>
#include <map>

#include "MyTest.hpp"


class VertexArray;
class VertexBuffer;
class IndexBuffer;
class Shader;
class MyTexture;
class Mesh;
class Material;
class Camera;


class MyTestBatchRendering3D : public MyTest
{
public:
	MyTestBatchRendering3D(const AppSystemData& appData);
	~MyTestBatchRendering3D();

	void OnLoop(float deltaTime) override;
	void OnRender() override;
	void OnGuiRender() override;

private:

    std::unique_ptr<VertexBuffer> m_DynamicVBO;

	float r, theta, phi, avoidanceGap;
	glm::vec3 m_SphericalCoord;

	int m_nMaxEntities, m_nRenderedEntities;
	std::unique_ptr<Camera> m_Camera;

	std::vector<float> m_Data;
	std::unique_ptr<Mesh> m_Mesh;
	std::unique_ptr<Material> m_Material;
};