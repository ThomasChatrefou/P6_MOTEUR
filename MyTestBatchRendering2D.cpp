#include "MyTestBatchRendering2D.hpp"

#include "Time.hpp"
#include "Renderer.hpp"
#include "GUI.hpp"

#include "Mesh.hpp"
#include "Material.hpp"
#include "Camera.hpp"

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "MyTexture.hpp"


#ifndef ShaderFile
#define ShaderFile
const std::string SHADER_FILE = "/resources/shaders/Batch.shader";
#endif // !ShaderFile

#ifndef TextureFile
#define TextureFile
const std::string TEXTURE_1 = "/resources/textures/zote.jpg";
const std::string TEXTURE_2 = "/resources/textures/awesomeface.png";
#endif // !TextureFile


MyTestBatchRendering2D::MyTestBatchRendering2D(const AppSystemData& appData)
    : t1(200.0f, 200.0f, 0.0f), t2(500.0f, 200.0f, 0.0f)
{
    app = appData;
    auto shaderPath = app.srcPath + SHADER_FILE;
    auto texture1 = app.srcPath + TEXTURE_1;
    auto texture2 = app.srcPath + TEXTURE_2;

    
    float vertices[] = {
        -100.0f, -100.0f, 0.0f, 0.0f,
         100.0f, -100.0f, 1.0f, 0.0f,
         100.0f,  100.0f, 1.0f, 1.0f,
        -100.0f,  100.0f, 0.0f, 1.0f,
    };

    unsigned int indices[] = {
        0,1,2,2,3,0,
    };

    m_Proj = glm::ortho(0.0f, (float)app.winWidth, 0.0f, (float)app.winHeight, -1.0f, 1.0f);
    m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    m_VAO = std::make_unique<VertexArray>();

    m_VBO = std::make_unique<VertexBuffer>(vertices, 4 * 4);
    VertexBufferLayout layout;
    layout.Push(2);
    layout.Push(2);
    m_VAO->AddBuffer(*m_VBO, layout);

    m_DynamicVBO = std::make_unique<VertexBuffer>(2 * 3);

    VertexBufferLayout layout2;
    layout2.Push(1);
    layout2.Push(2);
    m_VAO->AddBuffer(2, *m_DynamicVBO, layout2);
    

    m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

    m_Shader = std::make_unique<Shader>(shaderPath);
    m_Shader->Bind();
    auto loc = glGetUniformLocation(m_Shader->GetID(), "u_Textures");
    int samplers[2] = { 0,1 };
    glUniform1iv(loc, 2, samplers);

    m_Texture1 = std::make_unique<MyTexture>(texture1);
    m_Texture2 = std::make_unique<MyTexture>(texture2);

    m_VAO->Unbind();
    m_IndexBuffer->Unbind();
    m_Shader->Unbind();
}

MyTestBatchRendering2D::~MyTestBatchRendering2D()
{
}

void MyTestBatchRendering2D::OnLoop(float deltaTime)
{
}

void MyTestBatchRendering2D::OnRender()
{
    float data[] = {
           0.0f, t1.x, t1.y,
           1.0f, t2.x, t2.y
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_DynamicVBO->getID());
    glBufferSubData(GL_ARRAY_BUFFER, 0, 2 * 3 * sizeof(float), data);

    glVertexAttribDivisor(0, 0);
    glVertexAttribDivisor(1, 0);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);


    glBindTextureUnit(0, m_Texture1->getID());
    glBindTextureUnit(1, m_Texture2->getID());

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    glm::mat4 mvp = m_Proj * m_View * model;
    m_Shader->Bind();
    m_Shader->SetUniformMat4f("u_MVP", mvp);
    app.pRenderer->DrawInstanced(*m_VAO, *m_IndexBuffer, *m_Shader, 2);
   
}

void MyTestBatchRendering2D::OnGuiRender()
{
    app.pGUI->SetFixedWindowSize(250.0f, 100.0f);
    app.pGUI->PrintFPS(app.pClock->getDeltaTime());
    app.pGUI->BeginWindow("Debug", 520.0f, 0.0f, 500.0f, 100.0f);
    app.pGUI->AddSliderFloat3("TranslationA", t1, 0.0f, 1000.0f);
    app.pGUI->AddSliderFloat3("TranslationB", t2, 0.0f, 1000.0f);
    app.pGUI->EndWindow();
}