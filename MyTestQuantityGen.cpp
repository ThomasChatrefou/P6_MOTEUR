#include "MyTestQuantityGen.hpp"

#include <random>

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

#ifndef ModelsRepositoryPath
#define ModelsRepositoryPath
const std::string MODELS_REPOSITORY_PATH = "/resources/models";
#endif // !ModelsRepositoryPath


static std::mt19937 mersenneEngine(std::random_device{}());


MyTestQuantityGen::MyTestQuantityGen(const AppSystemData& appData)
    : m_nMaxEntities(50), m_nRenderedEntities(10), m_SphericalCoord(100.0f, 45.0f, 45.0f), avoidanceGap(4.0f)
{
    app = appData;
    auto shaderPath = app.srcPath + SHADER_FILE;

    std::filesystem::path repo{ app.srcPath + MODELS_REPOSITORY_PATH };
    for (auto const& dir_entry : std::filesystem::recursive_directory_iterator{ repo })
    {
        if (dir_entry.path().string().find(".fbx") != std::string::npos) 
        {
            m_Meshes.push_back(std::make_shared<Mesh>(dir_entry.path().string()));
        }
        if (dir_entry.path().string().find(".png") != std::string::npos)
        {
            m_Materials.push_back(std::make_shared<Material>(shaderPath, dir_entry.path().string()));
        }
    }
    //ASSUMING THAT EVERY .FBX FILE HAS A .PNG CORRESPONDING TO IT IN TEXTURE REPOSITORY
    m_nModels = m_Meshes.size();
    std::uniform_int_distribution<int> udistrib(0, m_nModels - 1);
    
    m_Camera = std::make_unique<Camera>();
    m_Camera->OnInit(glm::vec3(0.0f), glm::vec3(0.0f), 45.0f, (float)app.winWidth / (float)app.winHeight, 0.1f, 10000.0f);

    glm::mat4 proj = m_Camera->GetProjectionMatrix();
    glm::mat4 view = m_Camera->GetLookAtMatrix();

    int n = m_nMaxEntities;
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

                m_MVPs.push_back(proj * view * model);

                m_Entities.push_back(udistrib(mersenneEngine));
            }
        }
    }
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

    int n = m_nRenderedEntities;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                int index = (i * n + j) * n + k;
                glm::vec3 position = glm::vec3(
                    (i - n / 2) * avoidanceGap,
                    (j - n / 2) * avoidanceGap,
                    (k - n / 2) * avoidanceGap);

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                model = glm::translate(model, position);
                m_MVPs[index] = proj * view * model;

                m_Materials[m_Entities[index]]->UpdateMVP(m_MVPs[index]);
                app.pRenderer->Draw(*m_Meshes[m_Entities[index]], *m_Materials[m_Entities[index]]);
            }
        }
    }

}

void MyTestQuantityGen::OnGuiRender()
{
    app.pGUI->SetFixedWindowSize(250.0f, 100.0f);
    app.pGUI->PrintFPS(app.pClock->getDeltaTime());
    app.pGUI->BeginWindow("Debug", app.winWidth - 500.0f, 0.0f, 500.0f, 150.0f);

    app.pGUI->AddSliderInt("NMaxEntities", m_nRenderedEntities, 0, 50);
    ImGui::Text("nb of models : %d", m_nRenderedEntities * m_nRenderedEntities * m_nRenderedEntities);
    app.pGUI->AddSliderFloat3("Spherical Coord", m_SphericalCoord, 0.0f, 360.0f);
    app.pGUI->AddSliderFloat("Entities radius", avoidanceGap, 0.0f, 10.0f);

    app.pGUI->EndWindow();
}