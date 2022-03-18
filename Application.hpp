#pragma once

#include "OGLIncludes.hpp"

class Application
{
public:
    Application(int windowWidth, int windowHeight);

    int OnExecute();

private:
    bool m_AppRunning;

public: // game execution functions
    bool OnInit();
    void OnEvent(SDL_Event* currentEvent);
    void OnLoop();
    void OnRender();
    void OnCleanup();
};