#include "MyTestTexture2D.hpp"

#include "OGLIncludes.hpp"
#include "Time.hpp"
#include "GUI.hpp"
#include "Renderer.hpp"
#include "imgui.h"

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "MyTexture.hpp"


#ifndef ShaderFile
#define ShaderFile
const std::string SHADER_FILE = "resources/shaders/Basic.shader";
#endif // !ShaderFile

#ifndef TextureFile
#define TextureFile
const std::string TEXTURE_FILE = "resources/textures/zote.jpg";
#endif // !TextureFile


MyTestTexture2D::MyTestTexture2D(const TestHandlingData& testData)
    : m_TranslationA(200.0f,200.0f,0.0f), m_TranslationB(400.0f, 200.0f, 0.0f)
{
    data = testData;
    auto shaderPath = data.srcPath + SHADER_FILE;
    auto texturePath = data.srcPath + TEXTURE_FILE;
    float positions[] = {
        -100.0f, -100.0f, 0.0f, 0.0f,
         100.0f, -100.0f, 1.0f, 0.0f,
         100.0f,  100.0f, 1.0f, 1.0f,
        -100.0f,  100.0f, 0.0f, 1.0f,
    };
    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    m_Proj = glm::ortho(0.0f, (float)data.winWidth, 0.0f, (float)data.winHeight, -1.0f, 1.0f);
    m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    m_VAO = std::make_unique<VertexArray>();

    m_VBO = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push(2);
    layout.Push(2);
    m_VAO->AddBuffer(*m_VBO, layout);

    m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

    m_Shader = std::make_unique<Shader>(shaderPath);
    m_Shader->Bind();

    m_Texture = std::make_unique<MyTexture>(texturePath);
    m_Shader->SetUniform1i("u_Texture", 0);

    m_VAO->Unbind();
    m_IndexBuffer->Unbind();
    m_Shader->Unbind();
}

MyTestTexture2D::~MyTestTexture2D()
{
}


void MyTestTexture2D::OnLoop(float deltaTime)
{
}

void MyTestTexture2D::OnRender()
{
    data.pRenderer->Clear();
    m_Texture->Bind();

    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
        glm::mat4 mvp = m_Proj * m_View * model;
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        data.pRenderer->Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
        glm::mat4 mvp = m_Proj * m_View * model;
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        data.pRenderer->Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }
}

void MyTestTexture2D::OnGuiRender()
{
    data.pGUI->PrintFPS(data.pClock->getDeltaTime());
    data.pGUI->BeginWindow("Debug", 520.0f, 0.0f, 500.0f, 100.0f);
    data.pGUI->AddSliderFloat3("TranslationB", m_TranslationB, 0.0f, 1000.0f);
    data.pGUI->AddSliderFloat3("TranslationA", m_TranslationA, 0.0f, 1000.0f);
    data.pGUI->EndWindow();
}