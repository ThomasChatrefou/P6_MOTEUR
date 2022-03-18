#pragma once

#include "OGLIncludes.hpp"

class Application
{
public:
    Application(int windowWidth, int windowHeight);

    int OnExecute();

private:
    bool m_AppRunning;
    int m_Width;
    int m_Height;
    SDL_Window* m_Window;
    SDL_GLContext m_Context;

public: // game execution functions
    bool OnInit();
    void OnEvent(SDL_Event* currentEvent);
    void OnLoop();
    void OnRender();
    void OnCleanup();

public:
    bool Application::InitSDL();
    bool Application::InitWindow();
};