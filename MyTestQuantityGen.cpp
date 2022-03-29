#include "MyTestQuantityGen.hpp"

#include "Time.hpp"
#include "Renderer.hpp"
#include "GUI.hpp"
#include "imgui.h"

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


MyTestQuantityGen::MyTestQuantityGen(const AppSystemData& appData)
    : m_NMaxEntities(50), m_SphericalCoord(100.0f, 45.0f, 45.0f) 
{
    app = appData;
    auto shaderPath = app.srcPath + SHADER_FILE;
    auto texturePath = app.srcPath + CTHULHU_TEXTURE_FILE;
    auto meshPath = app.srcPath + CTHULHU_MESH_FILE;

    glm::vec3 camPos = glm::vec3(200.0f, 200.0f, 200.0f);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
    float fov = 45.0f;
    m_Camera = std::make_unique<Camera>();
    m_Camera->OnInit(camPos, target, fov, (float)app.winWidth / (float)app.winHeight, 0.1f, 10000.0f);

    glm::mat4 proj = m_Camera->GetProjectionMatrix();
    glm::mat4 view = m_Camera->GetLookAtMatrix();

    Mesh mesh(meshPath);
    Material material(shaderPath, texturePath);

    m_Mesh = std::make_unique<Mesh>(meshPath);
    m_Material = std::make_unique<Material>(shaderPath, texturePath);

    int n = m_NMaxEntities;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++) 
            {
                int index = (i * n + j) * n + k;
                glm::vec3 position = glm::vec3((i - n / 2) * 3.0f, (j - n / 2) * 3.0f, (k - n / 2) * 3.0f);
                //std::cout << position.x << " " << position.y << " " << position.z << std::endl;

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                model = glm::translate(model, position);

                m_MVPs.push_back(proj * view * model);
            }
        }
    }

    m_NMaxEntities = 10;
}

MyTestQuantityGen::~MyTestQuantityGen()
{
}

void MyTestQuantityGen::OnLoop(float deltaTime)
{
}

void MyTestQuantityGen::OnRender()
{
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

    int n = m_NMaxEntities;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                int index = (i * n + j) * n + k;
                glm::vec3 position = glm::vec3((i - n / 2) * 3.0f, (j - n / 2) * 3.0f, (k - n / 2) * 3.0f);

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                model = glm::translate(model, position);
                m_MVPs[index] = proj * view * model;

                m_Material->UpdateMVP(m_MVPs[index]);
                app.pRenderer->Draw(*m_Mesh, *m_Material);
            }
        }
    }
}

void MyTestQuantityGen::OnGuiRender()
{
    app.pGUI->SetFixedWindowSize(250.0f, 100.0f);
    app.pGUI->PrintFPS(app.pClock->getDeltaTime());
    app.pGUI->BeginWindow("Debug", app.winWidth - 500.0f, 0.0f, 500.0f, 150.0f);

    app.pGUI->AddSliderInt("NMaxEntities", m_NMaxEntities, 0, 50);
    ImGui::Text("nb of models : %d", m_NMaxEntities * m_NMaxEntities * m_NMaxEntities);
    app.pGUI->AddSliderFloat3("Spherical Coord", m_SphericalCoord, 0.0f, 360.0f);

    app.pGUI->EndWindow();
}