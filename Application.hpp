#pragma once

#include "OGLIncludes.hpp"
#include "Inputs.hpp"

class Application : public Inputs
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

    class Time* m_Clock;
    class GUI* m_GUI;

    //erase
    class Camera* cam;
    class Cthulhu* cthulhu;

public: // game execution functions
    bool OnInit();
    void OnEvent(SDL_Event* currentEvent);
    void OnLoop();
    void OnRender();
    void OnCleanup();

public: // init functions
    bool InitSDL();
    bool InitWindow();
    bool InitContext();
    bool InitGlew();

public: // event functions
    void OnQuit();

public: // render functions
    void ResetWindow();
};
