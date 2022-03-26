#pragma once

#include <memory>

#include "OGLIncludes.hpp"
#include "MyTest.hpp"


class VertexArray;
class VertexBuffer;
class IndexBuffer;
class Shader;
class MyTexture;


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

    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<MyTexture> m_Texture;
};