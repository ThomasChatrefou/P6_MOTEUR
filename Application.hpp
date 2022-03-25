#pragma once

#include "OGLIncludes.hpp"
#include "Inputs.hpp"

class Application : public Inputs
{
public:
    Application(const std::string& sourcePath, int windowWidth, int windowHeight);

    int OnExecute();

private:
    std::string m_SourcePath;
    bool m_AppRunning;
    int m_Width;
    int m_Height;
    SDL_Window* m_Window;
    SDL_GLContext m_Context;

    class Time* m_Clock;
    class GUI* m_GUI;
    class Renderer* m_Renderer;

    //temp
    glm::vec3 translationA;
    glm::vec3 translationB;
    class VertexArray* va;
    class VertexBuffer* vb;
    class IndexBuffer* ib;
    class Shader* shader;
    class MyTexture* texture;

    class Camera* cam;
    class Cthulhu* cthulhu;

    class MyTest* currentTest;
    class TestMenu* testMenu;
    class MyTestClearColor* test;

public: // game execution functions
    bool OnInit();
    void OnEvent(SDL_Event* currentEvent);
    void OnLoop();
    void OnRender();
    void OnGuiRender();
    void OnCleanup();

public: // init functions
    bool InitSDL();
    bool InitWindow();
    bool InitContext();
    bool InitGlew();
    void EnableVSync();
    void EnableBending();

public: // event functions
    void OnQuit();

};
