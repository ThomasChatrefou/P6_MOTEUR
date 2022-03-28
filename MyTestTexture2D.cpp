#include "MyTestTexture2D.hpp"

#include <string>

#include "Time.hpp"
#include "Renderer.hpp"
#include "GUI.hpp"

#include "Mesh.hpp"
#include "Material.hpp"


#ifndef ShaderFile
#define ShaderFile
//const std::string SHADER_FILE = "resources/shaders/Basic.shader";
const std::string SHADER_FILE = "resources/shaders/BasicLightning.shader";
#endif // !ShaderFile

#ifndef TextureFile
#define TextureFile
const std::string TEXTURE_FILE = "resources/textures/zote.jpg";
#endif // !TextureFile


MyTestTexture2D::MyTestTexture2D(const AppSystemData& appData)
    : m_TranslationA(200.0f, 200.0f, 0.0f), m_TranslationB(400.0f, 200.0f, 0.0f)
{
    app = appData;
    auto shaderPath = app.srcPath + SHADER_FILE;
    auto texturePath = app.srcPath + TEXTURE_FILE;
    float data[] = {
        -100.0f, -100.0f, 0.0f, 0.0f,
         100.0f, -100.0f, 1.0f, 0.0f,
         100.0f,  100.0f, 1.0f, 1.0f,
        -100.0f,  100.0f, 0.0f, 1.0f,
    };
    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    m_Proj = glm::ortho(0.0f, (float)app.winWidth, 0.0f, (float)app.winHeight, -1.0f, 1.0f);
    m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    MeshData meshData = { data, indices, 16, 6, 2 };
    m_Mesh = std::make_unique<Mesh>(meshData, true, false);
    m_Material = std::make_unique<Material>(shaderPath, texturePath);

    m_Mesh->Unbind();
    m_Material->Unbind();
}

MyTestTexture2D::~MyTestTexture2D()
{
}

void MyTestTexture2D::OnRender()
{
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
        glm::mat4 mvp = m_Proj * m_View * model;
        m_Material->UpdateMVP(mvp);
        app.pRenderer->Draw(*m_Mesh, *m_Material);
    }
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
        glm::mat4 mvp = m_Proj * m_View * model;
        m_Material->UpdateMVP(mvp);
        app.pRenderer->Draw(*m_Mesh, *m_Material);
    }
}

void MyTestTexture2D::OnGuiRender()
{
    app.pGUI->SetFixedWindowSize(250.0f, 100.0f);
    app.pGUI->PrintFPS(app.pClock->getDeltaTime());
    app.pGUI->BeginWindow("Debug", 520.0f, 0.0f, 500.0f, 100.0f);
    app.pGUI->AddSliderFloat3("TranslationB", m_TranslationB, 0.0f, 1000.0f);
    app.pGUI->AddSliderFloat3("TranslationA", m_TranslationA, 0.0f, 1000.0f);
    app.pGUI->EndWindow();
}