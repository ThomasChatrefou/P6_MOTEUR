#include "Application.hpp"
#include "GetAppPath.hpp"



#ifndef ShadersPath
char* SHADERS_REPOSITORY_NAME = "shaders";
char* VERTEX_SHADERS_FILE_NAME = "SimpleVertexShader.glsl";
char* FRAGMENT_SHADERS_FILE_NAME = "SimpleFragmentShader.glsl";
#endif //ShaderPath


Application::Application(int windowWidth, int windowHeight)
{
    m_AppRunning = true;
    m_Width = windowWidth;
    m_Height = windowHeight;
}

int Application::OnExecute()
{
    if (OnInit() == false)
    {
        return -1;
    }

    SDL_Event currentEvent;

    while (m_AppRunning)
    {
        while (SDL_PollEvent(&currentEvent))
        {
            OnEvent(&currentEvent);
        }

        OnLoop();

        OnRender();
    }

    OnCleanup();

    return 0;
}

bool Application::OnInit()
{
    std::cout << "Hello" << std::endl;

    if (!InitSDL()) return false;
    if (!InitWindow()) return false;

	return true;
}

void Application::OnEvent(SDL_Event* currentEvent)
{
}

void Application::OnLoop()
{
}

void Application::OnRender()
{
}

void Application::OnCleanup()
{
}

//////////////////////////////////////////////////////

bool Application::InitSDL()
{
    std::cout << "Initializing SDL" << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO) >= 0) return true;

    std::cout << "SDL init failed" << std::endl;
    return false;
}

bool Application::InitWindow()
{
    std::cout << "Creating Window" << std::endl;

    uint32_t windowsFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    m_Window = SDL_CreateWindow("MyEngine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        m_Width,
        m_Height,
        windowsFlags);

    if (m_Window != NULL) return true;

    std::cout << "SDL window creation failed" << std::endl;
    return false;
}
