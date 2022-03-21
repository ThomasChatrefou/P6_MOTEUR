#include "Application.hpp"
#include "GUI.hpp"
#include "Time.hpp"
#include "Buffer.hpp"
#include "Mesh.hpp"




Application::Application(int windowWidth, int windowHeight)
{
    m_AppRunning = true;
    m_Width = windowWidth;
    m_Height = windowHeight;
    m_Window = NULL;
    m_Context = NULL;

    m_Clock = new Time();
    m_GUI = nullptr;
    
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

//////////////////////////////////////////////////////

bool Application::OnInit()
{
    std::cout << "====== INIT ======" << std::endl;

    if (!InitSDL()) return false;
    if (!InitWindow()) return false;
    if (!InitContext()) return false;
    if (!InitGlew()) return false;

    m_GUI = new GUI(m_Window, m_Context);
    if (!m_GUI->OnInit()) return false;
    
    std::cout << "==== END INIT ====" << std::endl;


    Buffer OBuffer;
    OBuffer.Vao();
    OBuffer.CreateBuffer(1, CubeVertices, sizeof(CubeVertices));
    OBuffer.BindBufferToAttrib(0, 3, 5 * sizeof(float), 0);
    OBuffer.BindBufferToAttrib(1, 2, 5 * sizeof(float), (3 * sizeof(float)));


	return true;
}

void Application::OnEvent(SDL_Event* currentEvent)
{
    m_GUI->OnEvent(currentEvent);
    Inputs::OnEvent(currentEvent);
}

void Application::OnLoop()
{
    m_Clock->OnLoop();
    m_GUI->OnLoop();
    m_GUI->PrintFPS(m_Clock->getDeltaTime());
}

void Application::OnRender()
{
    ResetWindow();
    m_GUI->OnRender();

    //  RENDERING STUFF
   

    //  END RENDERING

    SDL_GL_SwapWindow(m_Window);
}

void Application::OnCleanup()
{
    m_GUI->OnCleanup();
    SDL_Quit();
}

//////////////////////////////////////////////////////

bool Application::InitSDL()
{
    std::cout << "Initializing SDL" << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO) >= 0) return true;

    std::cout << "ERROR: SDL init failed" << std::endl;
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

    // Permet d'utiliser renderProfile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    if (m_Window != NULL) return true;

    std::cout << "ERROR: SDL window creation failed" << std::endl;
    return false;
}

bool Application::InitContext()
{
    std::cout << "Creating Context" << std::endl;

    m_Context = SDL_GL_CreateContext(m_Window);

    if (m_Context != NULL)
    {
        if (SDL_GL_MakeCurrent(m_Window, m_Context) >= 0) return true;

        std::cout << "ERROR: OpenGL context setup failed" << std::endl;
        return false;
    }

    std::cout << "ERROR: SDL context creation failed" << std::endl;
    return false;
}

bool Application::InitGlew()
{
    std::cout << "Initializing Glew" << std::endl;
    glewExperimental = true;
    if (glewInit() == GLEW_OK) return true;

    std::cout << "ERROR: Glew init failed" << std::endl;
    return false;
}

//////////////////////////////////////////////////////

void Application::OnQuit()
{
    m_AppRunning = false;
}

//////////////////////////////////////////////////////

void Application::ResetWindow()
{
    glViewport(0, 0, m_Width, m_Height);
    glClearColor(0.13f, 0.13f, 0.13f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}