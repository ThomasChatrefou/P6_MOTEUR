#include "MyTestBatchRendering3D.hpp"

#include <random>

#include "Time.hpp"
#include "Renderer.hpp"
#include "GUI.hpp"
#include "imgui.h"

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
const std::string SHADER_FILE = "/resources/shaders/BatchRendering3D.shader";
#endif // !ShaderFile

#ifndef CthulhuTextureFile
#define CthulhuTextureFile
const std::string CTHULHU_TEXTURE_FILE = "/resources/textures/Cthulhu_Texture.png";
#endif // !CthulhuTextureFile

#ifndef CthulhuMeshFile
#define CthulhuMeshFile
const std::string CTHULHU_MESH_FILE = "/resources/models/Cthulhu.fbx";
#endif // !CthulhuMeshFilelsRepositoryPath


MyTestBatchRendering3D::MyTestBatchRendering3D(const AppSystemData& appData)
    : m_nMaxEntities(100), m_nRenderedEntities(5), m_SphericalCoord(100.0f, 45.0f, 45.0f), avoidanceGap(4.0f)
{
    app = appData;
    auto shaderPath = app.srcPath + SHADER_FILE;
    auto texturePath = app.srcPath + CTHULHU_TEXTURE_FILE;
    auto meshPath = app.srcPath + CTHULHU_MESH_FILE;

    m_Mesh = std::make_unique<Mesh>(meshPath);

    m_DynamicVBO = std::make_unique<VertexBuffer>(m_nMaxEntities * m_nMaxEntities * m_nMaxEntities * 3);
    VertexBufferLayout layout;
    layout.Push(3);
    m_Mesh->getVAO()->AddBuffer(3, *m_DynamicVBO, layout);

    m_Material = std::make_unique<Material>(shaderPath, texturePath);

    m_Camera = std::make_unique<Camera>();
    m_Camera->OnInit(glm::vec3(0.0f), glm::vec3(0.0f), 45.0f, (float)app.winWidth / (float)app.winHeight, 0.1f, 10000.0f);

    glm::mat4 proj = m_Camera->GetProjectionMatrix();
    glm::mat4 view = m_Camera->GetLookAtMatrix();

    m_Data.resize(m_nMaxEntities * m_nMaxEntities * m_nMaxEntities * 3);
}

MyTestBatchRendering3D::~MyTestBatchRendering3D()
{
}

void MyTestBatchRendering3D::OnLoop(float deltaTime)
{
}

void MyTestBatchRendering3D::OnRender()
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

                m_Data[index * 3] = position.x;
                m_Data[index * 3 + 1] = position.y;
                m_Data[index * 3 + 2] = position.z;
            }
        }
    }
    m_Mesh->getVAO()->Bind();

    m_Material->Bind();

    glBindBuffer(GL_ARRAY_BUFFER, m_DynamicVBO->getID());
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_Data.size() * sizeof(float), m_Data.data());

    glVertexAttribDivisor(0, 0);
    glVertexAttribDivisor(1, 0);
    glVertexAttribDivisor(3, 1);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    glm::mat4 mvp = proj * view * model;
    m_Material->UpdateMVP(mvp);
    int nRenderedEntities = m_nRenderedEntities * m_nRenderedEntities * m_nRenderedEntities;
    app.pRenderer->DrawInstanced(*m_Mesh->getVAO(), *m_Mesh->getIndexBuffer(), *m_Material->GetShader(), nRenderedEntities);
}

void MyTestBatchRendering3D::OnGuiRender()
{
    app.pGUI->SetFixedWindowSize(250.0f, 100.0f);
    app.pGUI->PrintFPS(app.pClock->getDeltaTime());
    app.pGUI->BeginWindow("Debug", 520.0f, 0.0f, 500.0f, 150.0f);

    app.pGUI->AddSliderInt("NMaxEntities", m_nRenderedEntities, 0, 100);
    ImGui::Text("nb of models : %d", m_nRenderedEntities * m_nRenderedEntities * m_nRenderedEntities);
    app.pGUI->AddSliderFloat3("Spherical Coord", m_SphericalCoord, 0.0f, 360.0f);
    app.pGUI->AddSliderFloat("Entities radius", avoidanceGap, 0.0f, 10.0f);

    app.pGUI->EndWindow();
}