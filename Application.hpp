#pragma once
#include<memory>

#include "OGLIncludes.hpp"
#include "Inputs.hpp"


class Time;
class Renderer;
class GUI;
class MyTest;
class TestMenu;


class Application : public Inputs
{
public:
    Application(const std::string& appPath, int windowWidth, int windowHeight);
    ~Application() {}

    int OnExecute();

private:
    std::string m_AppPath;
    bool m_AppRunning;
    int m_Width;
    int m_Height;
    SDL_Window* m_Window;
    SDL_GLContext m_Context;

    std::shared_ptr<Time> m_Clock;
    std::shared_ptr<Renderer> m_Renderer;
    std::shared_ptr<GUI> m_GUI;

    class MyTest* currentTest;
    class TestMenu* testMenu;

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

public: // event functions
    void OnQuit();
};
