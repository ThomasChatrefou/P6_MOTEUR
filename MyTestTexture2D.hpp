#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "MyTest.hpp"


class Mesh;
class Material;


class MyTestTexture2D : public MyTest
{
public:
	MyTestTexture2D(const AppSystemData& appData);
	~MyTestTexture2D();

	void OnRender() override;
	void OnGuiRender() override;

private:
    glm::vec3 m_TranslationA;
    glm::vec3 m_TranslationB;
    glm::mat4 m_Proj;
    glm::mat4 m_View;

    std::unique_ptr<Mesh> m_Mesh;
    std::unique_ptr<Material> m_Material;
};