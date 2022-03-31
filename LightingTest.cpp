#include "LightingTest.hpp"

#include "imgui.h"
#include "Time.hpp"
#include "Renderer.hpp"
#include "GUI.hpp"

#ifndef ShaderFile
#define ShaderFile
const std::string SHADER_FILE = "/resources/shaders/BasicLighting.shader";
#endif // !ShaderFile

#ifndef CthulhuTextureFile
#define CthulhuTextureFile
const std::string CTHULHU_TEXTURE_FILE = "/resources/textures/Cthulhu_Texture.png";
#endif // !CthulhuTextureFile

#ifndef CthulhuMeshFile
#define CthulhuMeshFile
const std::string CTHULHU_MESH_FILE = "/resources/models/Cthulhu.fbx";
#endif // !CthulhuMeshFile

#ifndef CactusTextureFile
#define CactusTextureFile
const std::string CACTUS_TEXTURE_FILE = "/resources/textures/Cactus_Texture.png";
#endif // !CactusTextureFile

#ifndef CactusMeshFile
#define CactusMeshFile
const std::string CACTUS_MESH_FILE = "/resources/models/Cactus.fbx";
#endif // !CactusMeshFile


LightingTest::LightingTest(const AppSystemData& appData)
    : m_Translation(0.0f, 0.0f, 0.0f), m_Rotation(0.0f, 0.0f, 0.0f), lightColor{ 1.0f, 1.0f, 1.0f, 1.0f }, m_SphericalCoord(10.0f, 45.0f, 45.0f)
{
    //-------------------Directory------------------------------//

    app = appData;
    auto shaderPath = app.srcPath + SHADER_FILE;
    
    auto cthulhuTexturePath = app.srcPath + CTHULHU_TEXTURE_FILE;
    auto cthulhuMeshPath = app.srcPath + CTHULHU_MESH_FILE;

    auto kaktusTexturePath = app.srcPath + CACTUS_TEXTURE_FILE;
    auto kaktusMeshPath = app.srcPath + CACTUS_MESH_FILE;

    //-------------------Directory------------------------------//

    //temp -> put this into scene
    glm::vec3 camPos = glm::vec3(0.0f, 0.0f, -10.0f);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
    float fov = 45.0f;

    //-------------------Init Light------------------------------//

    lightPos = glm::vec3(0.0f, 0.5f, 0.0f);
    ambientStrength = 0.1f;
    specularStrength = 1.0f;
    specularPower = 6;

    //-------------------View------------------------------//

    m_Camera = std::make_unique<Camera>();
    m_Camera->OnInit(camPos, target, fov, (float)app.winWidth / (float)app.winHeight, 0.1f, 100.0f);
    m_Proj = m_Camera->GetProjectionMatrix();
    m_View = m_Camera->GetLookAtMatrix();
    //----------------------------------------------------------------------------------------------//

    m_Meshes.push_back(std::make_shared<Mesh>(cthulhuMeshPath));
    m_Materials.push_back(std::make_shared<Material>(shaderPath, cthulhuTexturePath));

    m_Meshes.push_back(std::make_shared<Mesh>(kaktusMeshPath));
    m_Materials.push_back(std::make_shared<Material>(shaderPath, kaktusTexturePath));

    m_CurrentMesh = m_Meshes[0];
    m_CurrentMaterial = m_Materials[0];

    m_CurrentMesh->Unbind();
    m_CurrentMaterial->Unbind();
}

LightingTest::~LightingTest()
{

}

void LightingTest::OnLoop(float deltaTime)
{
}

void LightingTest::OnRender()
{
    //-------------------------------Camera Spherique----------------------------------------//

    r = m_SphericalCoord.x;
    theta = m_SphericalCoord.y;
    phi = m_SphericalCoord.z;
    glm::vec3 camPosition = glm::vec3(
        r * glm::cos(glm::radians(theta)) * glm::sin(glm::radians(phi)),
        r * glm::cos(glm::radians(phi)),
        r * glm::sin(glm::radians(theta)) * glm::sin(glm::radians(phi)));
    m_Camera->SetPosition(camPosition);
    glm::mat4 proj = m_Camera->GetProjectionMatrix();
    glm::mat4 view = m_Camera->GetLookAtMatrix();

    //-------------------------------Shader----------------------------------------//

    m_CurrentMaterial->Bind();
    m_CurrentMaterial->SetVec3("objectColor", 1.0f, 1.0f, 1.0f);
    m_CurrentMaterial->SetVec3("lightColor", lightColor[0], lightColor[1], lightColor[2]);
    m_CurrentMaterial->SetVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);
    m_CurrentMaterial->SetVec3("viewPos", m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z);
    m_CurrentMaterial->SetFloat("ambientStrength", ambientStrength);
    m_CurrentMaterial->SetFloat("specularStrength", specularStrength);
    m_CurrentMaterial->SetInt("specularPower", std::pow(2, specularPower));

    //-------------------------------Matrice----------------------------------------//

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
    model = glm::rotate(model, m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, m_Translation);
    glm::mat4 mvp = proj * view * model;

    //-----------------------------------------------------------------------------//
    m_CurrentMaterial->UpdateMVP(mvp);
    app.pRenderer->Draw(*m_CurrentMesh, *m_CurrentMaterial);
}

void LightingTest::OnGuiRender()
{
    //----------------------------IMGUI WINDOW-------------------------------//
    app.pGUI->SetFixedWindowSize(250.0f, 100.0f);
    app.pGUI->PrintFPS(app.pClock->getDeltaTime());

    //----------------------------Model Movement-------------------------------//

    app.pGUI->BeginWindow("Movements", 520.0f, 0.0f, 500.0f, 250.0f);
    //------------------------------------------------------------------------------------//
    app.pGUI->AddSliderFloat3("Translation", m_Translation, -10.0f, 10.0f);
    app.pGUI->AddSliderFloat3("Rotation", m_Rotation, 0.0f, glm::radians(360.0f));
    app.pGUI->AddSliderFloat3("Light Position", lightPos, -10.0f, 10.0f);
    //--------------Orbital Camera-------------//
    ImGui::Text("Spherical movements");
    app.pGUI->AddSliderFloat("Distance", m_SphericalCoord.x, 0.0f, 10.0f);
    app.pGUI->AddSliderFloat("Longitude", m_SphericalCoord.y, 0.0f, 360.0f);
    app.pGUI->AddSliderFloat("Colatitude", m_SphericalCoord.z, 0.0f, 180.0f);
    //------------------------------------------------------------------------------------//
    app.pGUI->EndWindow();


    //----------------------------Light Settings-------------------------------//

    app.pGUI->BeginWindow("Light Settings", app.winWidth - 500.0f, 0.0f, 500.0f, 200.0f);
    //------------------------------------------------------------------------------------//
    app.pGUI->AddSliderFloat("Ambiant Strength", ambientStrength, 0.0f, 1.0f);
    app.pGUI->AddSliderFloat("Specular Strength", specularStrength, 0.0f, 1.0f);
    app.pGUI->AddSliderInt("Specular Power", specularPower, 0, 8);
    app.pGUI->AddColorEdit4("Light Color", lightColor);
    //-----------------------------------------------------------------------------------//
    app.pGUI->EndWindow();


    //=========================================================
    app.pGUI->BeginWindow("Mesh", 0.0f, app.winHeight - 90.0f, 250.0f, 90.0f);
    //-----------------------------------------------//

    if (app.pGUI->AddButton("Invoke the mighty Cthulhu"))
    {
        m_CurrentMesh = m_Meshes[0];
        m_CurrentMaterial = m_Materials[0];
    }
    if (app.pGUI->AddButton("Invoke the terrible Kaktus"))
    {
        m_CurrentMesh = m_Meshes[1];
        m_CurrentMaterial = m_Materials[1];
    }
    //-----------------------------------------------//
    app.pGUI->EndWindow();
}