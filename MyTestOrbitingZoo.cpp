#include "MyTestOrbitingZoo.hpp"

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

#ifndef CthulhuTextureFile
#define CthulhuTextureFile
const std::string CTHULHU_TEXTURE_FILE = "/resources/textures/Cthulhu_Texture.png";
#endif // !CthulhuTextureFile

#ifndef CthulhuMeshFile
#define CthulhuMeshFile
const std::string CTHULHU_MESH_FILE = "/resources/models/Cthulhu.fbx";
#endif // !CthulhuMeshFile

#ifndef ModelsRepositoryPath
#define ModelsRepositoryPath
const std::string MODELS_REPOSITORY_PATH = "/resources/models";
#endif // !ModelsRepositoryPath


static std::mt19937 mersenneEngine(std::random_device{}());


MyTestOrbitingZoo::MyTestOrbitingZoo(const AppSystemData& appData)
    : m_nMaxEntities(20), m_nRenderedEntities(1),
    r(10.0f), phi(90.0f), aspeed(50.0f),
    rAmp(1.0f), thetaMax(360.0f), phiAmp(5.0f), aspeedAmp(1.0f)
{
    app = appData;
    auto shaderPath = app.srcPath + SHADER_FILE;
    auto texturePath = app.srcPath + CTHULHU_TEXTURE_FILE;
    auto meshPath = app.srcPath + CTHULHU_MESH_FILE;

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

    std::uniform_real_distribution<float> radiusDistrib(r - rAmp, r + rAmp);
    std::uniform_real_distribution<float> thetaDistrib(0.0f, thetaMax);
    std::uniform_real_distribution<float> phiDistrib(phi - phiAmp, phi + phiAmp);
    std::uniform_real_distribution<float> angularSpeedDistrib(aspeed - aspeedAmp, aspeed + aspeedAmp);

    m_Camera = std::make_unique<Camera>();
    m_Camera->OnInit(glm::vec3(0.5f, 50.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f), 45.0f, (float)app.winWidth / (float)app.winHeight, 0.1f, 10000.0f);

    m_Proj = m_Camera->GetProjectionMatrix();
    m_View = m_Camera->GetLookAtMatrix();

    int n = m_nMaxEntities;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++) 
            {
                int index = (i * n + j) * n + k;

                float rr = radiusDistrib(mersenneEngine);
                float rtheta = thetaDistrib(mersenneEngine);
                float rphi = phiDistrib(mersenneEngine);
                float raspeed = angularSpeedDistrib(mersenneEngine);

                glm::vec3 sc{ rr, rtheta, rphi };

                glm::vec3 position = glm::vec3(
                    rr * glm::cos(glm::radians(rtheta)) * glm::sin(glm::radians(rphi)),
                    rr * glm::cos(glm::radians(rphi)),
                    rr * glm::sin(glm::radians(rtheta)) * glm::sin(glm::radians(rphi)));

                m_Entities.push_back({ udistrib(mersenneEngine), raspeed, sc });
            }
        }
    }
}

MyTestOrbitingZoo::~MyTestOrbitingZoo()
{
}

void MyTestOrbitingZoo::OnLoop(float deltaTime)
{
    
}

void MyTestOrbitingZoo::OnRender()
{

    int n = m_nRenderedEntities;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                int index = (i * n + j) * n + k;

                Entity e = m_Entities[index];
                float er = e.sphericalCoord.x;
                float etheta = e.sphericalCoord.y + e.aspeed * app.pClock->getDeltaTime();
                if (etheta > 360.0f)  etheta -= 360.0f;
                m_Entities[index].sphericalCoord.y = etheta;
                float ephi = e.sphericalCoord.z;
                glm::vec3 position = glm::vec3(
                    er * glm::cos(glm::radians(etheta)) * glm::sin(glm::radians(ephi)),
                    er * glm::cos(glm::radians(ephi)),
                    er * glm::sin(glm::radians(etheta)) * glm::sin(glm::radians(ephi)));

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, position);
                //model = model * glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                glm::mat4 mvp = m_Proj * m_View * model;

                m_Materials[m_Entities[index].modelID]->UpdateMVP(mvp);
                app.pRenderer->Draw(*m_Meshes[m_Entities[index].modelID], *m_Materials[m_Entities[index].modelID]);
            }
        }
    }

}

void MyTestOrbitingZoo::OnGuiRender()
{
    app.pGUI->SetFixedWindowSize(250.0f, 100.0f);
    app.pGUI->PrintFPS(app.pClock->getDeltaTime());
    app.pGUI->BeginWindow("Debug", app.winWidth - 500.0f, 0.0f, 500.0f, 150.0f);

    app.pGUI->AddSliderInt("NMaxEntities", m_nRenderedEntities, 0, 20);
    ImGui::Text("nb of drawn entities : %d", m_nRenderedEntities * m_nRenderedEntities * m_nRenderedEntities);

    app.pGUI->EndWindow();
}