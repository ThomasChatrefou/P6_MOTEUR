#include "MyTestSkyBox.hpp"

#include "Time.hpp"
#include "Renderer.hpp"
#include "GUI.hpp"
#include <stb_image.h>

#ifndef FRAGFile
#define FRAGFile
const std::string FRAG_FILE = "/resources/shaders/SkyboxFShader.glsl";
#endif // !ShaderFile

#ifndef VERTEXFile
#define VERTEXFile
const std::string VERTEX_FILE = "/resources/shaders/SkyboxVShader.shader";
#endif // !ShaderFile

MyTestSkyBox::MyTestSkyBox(const AppSystemData& appData)
{
    app = appData;
    auto VSPath = app.srcPath + VERTEX_FILE;
    auto FSPath = app.srcPath + FRAG_FILE;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    // skybox VAO

    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    cubemapTexture = loadCubemap(faces);

    skyboxShader = SkyboxShader(VSPath.c_str(), FSPath.c_str());
    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);

}

MyTestSkyBox::~MyTestSkyBox()
{
}

void MyTestSkyBox::OnLoop(float deltaTime)
{
}

void MyTestSkyBox::OnRender()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // draw skybox as last
    glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    skyboxShader.use();

    glm::vec3 camPos = glm::vec3(0.0f, 0.0f, -10.0f);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
    float fov = 45.0f;

    m_Camera = std::make_unique<Camera>();
    m_Camera->OnInit(camPos, target, fov, (float)app.winWidth / (float)app.winHeight, 0.1f, 100.0f);
    m_Proj = m_Camera->GetProjectionMatrix();
    m_View = m_Camera->GetLookAtMatrix();

    skyboxShader.setMat4("view", m_View);
    skyboxShader.setMat4("projection", m_Proj);

    // skybox cube
    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS); // set depth function back to default

}

void MyTestSkyBox::OnGuiRender()
{
}

unsigned int MyTestSkyBox::loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}