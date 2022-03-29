#include "LightingTest.hpp"


#include "Time.hpp"
#include "Renderer.hpp"
#include "GUI.hpp"

#ifndef ShaderFile
#define ShaderFile
//const std::string SHADER_FILE = "resources/shaders/Basic.shader";
const std::string SHADER_FILE = "resources/shaders/BasicLighting.shader";
#endif // !ShaderFile

#ifndef CthulhuTextureFile
#define CthulhuTextureFile
const std::string CTHULHU_TEXTURE_FILE = "resources/textures/Cthulhu_Texture.png";
#endif // !CthulhuTextureFile

#ifndef CthulhuMeshFile
#define CthulhuMeshFile
const std::string CTHULHU_MESH_FILE = "resources/models/Cthulhu.fbx";
#endif // !CthulhuMeshFile

LightingTest::LightingTest(const AppSystemData& appData) : m_Translation(0.0f, 0.0f, 0.0f), m_Rotation(0.0f, 0.0f, 0.0f)
{
    app = appData;
    auto shaderPath = app.srcPath + SHADER_FILE;
    auto texturePath = app.srcPath + CTHULHU_TEXTURE_FILE;
    auto meshPath = app.srcPath + CTHULHU_MESH_FILE;
	lightPos = glm::vec3(0.0f, 0.5f, 0.0f);

    //temp -> put this into scene
    glm::vec3 camPos = glm::vec3(0.0f, 0.0f, -10.0f);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
    float fov = 45.0f;

    ambientStrength = 0.1f;
    specularStrength = 1.0f;
    specularPower = 6;

    m_Camera = std::make_unique<Camera>();
    m_Camera->OnInit(camPos, target, fov, (float)app.winWidth / (float)app.winHeight, 0.1f, 100.0f);
    m_Proj = m_Camera->GetProjectionMatrix();
    m_View = m_Camera->GetLookAtMatrix();

    m_Mesh = std::make_unique<Mesh>(meshPath);
    m_Material = std::make_unique<Material>(shaderPath, texturePath);

    m_Mesh->Unbind();
    m_Material->Unbind();
}

LightingTest::~LightingTest()
{

}

void LightingTest::OnLoop(float deltaTime)
{
}

void LightingTest::OnRender()
{
    m_Material->Bind();

    m_Material->SetVec3("objectColor", 1.0f, 1.0f, 1.0f);
    m_Material->SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
    m_Material->SetVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);
    m_Material->SetVec3("viewPos", m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z);

    m_Material->SetFloat("ambientStrength", ambientStrength);
    m_Material->SetFloat("specularStrength", specularStrength);
    m_Material->SetInt("specularPower", std::pow(2, specularPower));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
    model = glm::rotate(model, m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, m_Translation);
    glm::mat4 mvp = m_Proj * m_View * model;

    m_Material->UpdateMVP(mvp);
    app.pRenderer->Draw(*m_Mesh, *m_Material);
}

void LightingTest::OnGuiRender()
{
    app.pGUI->SetFixedWindowSize(250.0f, 100.0f);
    app.pGUI->PrintFPS(app.pClock->getDeltaTime());
    app.pGUI->BeginWindow("Movements", 520.0f, 0.0f, 500.0f, 100.0f);

    app.pGUI->AddSliderFloat3("Translation", m_Translation, -10.0f, 10.0f);
    app.pGUI->AddSliderFloat3("Rotation", m_Rotation, 0.0f, glm::radians(360.0f));
    app.pGUI->EndWindow();

    app.pGUI->BeginWindow("Light Settings", app.winWidth - 500.0f, 0.0f, 500.0f, 150.0f);
    app.pGUI->AddSliderFloat("Ambiant Strength", ambientStrength, 0.0f, 1.0f);
    app.pGUI->AddSliderFloat("Specular Strength", specularStrength, 0.0f, 1.0f);
    app.pGUI->AddSliderInt("Specular Power", specularPower, 0, 8);
    app.pGUI->EndWindow();
}