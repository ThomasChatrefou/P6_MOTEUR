#include "Application.hpp"

Application::Application(int windowWidth, int windowHeight)
{
}

int Application::OnExecute()
{
    std::cout << "Hello" << std::endl;
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
