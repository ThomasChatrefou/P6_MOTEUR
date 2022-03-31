#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "MyTest.hpp"


class VertexArray;
class VertexBuffer;
class IndexBuffer;
class Shader;
class MyTexture;


class MyTestBatchRendering2D : public MyTest
{
public:
	MyTestBatchRendering2D(const AppSystemData& appData);
	~MyTestBatchRendering2D();

	void OnLoop(float deltaTime) override;
	void OnRender() override;
	void OnGuiRender() override;

private:
    glm::vec3 t1;
    glm::vec3 t2;
    glm::mat4 m_Proj;
    glm::mat4 m_View;

    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<VertexBuffer> m_DynamicVBO;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<MyTexture> m_Texture1;
    std::unique_ptr<MyTexture> m_Texture2;
};