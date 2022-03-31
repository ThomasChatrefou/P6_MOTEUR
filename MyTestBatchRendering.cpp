#include "MyTestBatchRendering.hpp"

#include "Time.hpp"
#include "Renderer.hpp"
#include "GUI.hpp"

#include "Mesh.hpp"
#include "Material.hpp"
#include "Camera.hpp"


#ifndef ShaderFile
#define ShaderFile
const std::string SHADER_FILE = "/resources/shaders/Basic.shader";
#endif // !ShaderFile

#ifndef CthulhuTextureFile
#define CthulhuTextureFile
const std::string CTHULHU_TEXTURE_FILE = "/resources/textures/Cthulhu_Texture.png";
#endif // !CthulhuTextureFile

#ifndef CthulhuMeshFile
#define CthulhuMeshFile
const std::string CTHULHU_MESH_FILE = "/resources/models/Cthulhu.fbx";
#endif // !CthulhuMeshFile


MyTestBatchRendering::MyTestBatchRendering(const AppSystemData& appData)
    : m_Translation(0.0f, 0.0f, -1.5f), m_Rotation(90.0f, 180.0f, 0.0f)
{
    app = appData;
    auto shaderPath = app.srcPath + SHADER_FILE;
    auto texturePath = app.srcPath + CTHULHU_TEXTURE_FILE;
    auto meshPath = app.srcPath + CTHULHU_MESH_FILE;

    //temp -> put this into scene
    glm::vec3 camPos = glm::vec3(0.0f, 0.0f, -10.0f);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
    float fov = 45.0f;

    m_Camera = std::make_unique<Camera>();
    m_Camera->OnInit(camPos, target, fov, (float)app.winWidth / (float)app.winHeight, 0.1f, 100.0f);
    m_Proj = m_Camera->GetProjectionMatrix();
    m_View = m_Camera->GetLookAtMatrix();

    m_Mesh = std::make_unique<Mesh>(meshPath);
    m_Material = std::make_unique<Material>(shaderPath, texturePath);

    m_Mesh->Unbind();
    m_Material->Unbind();
}

MyTestBatchRendering::~MyTestBatchRendering()
{
}

void MyTestBatchRendering::OnLoop(float deltaTime)
{
}

void MyTestBatchRendering::OnRender()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, m_Translation);
    glm::mat4 mvp = m_Proj * m_View * model;

    m_Material->UpdateMVP(mvp);
    app.pRenderer->Draw(*m_Mesh, *m_Material);
}

void MyTestBatchRendering::OnGuiRender()
{
    app.pGUI->SetFixedWindowSize(250.0f, 100.0f);
    app.pGUI->PrintFPS(app.pClock->getDeltaTime());
    app.pGUI->BeginWindow("Debug", 520.0f, 0.0f, 500.0f, 100.0f);
    app.pGUI->AddSliderFloat3("Translation", m_Translation, -10.0f, 10.0f);
    app.pGUI->AddSliderFloat3("Rotation", m_Rotation, 0.0f, 360.0f);
    app.pGUI->EndWindow();
}