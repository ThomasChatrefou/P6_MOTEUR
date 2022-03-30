#include "Application.hpp"

#include "Time.hpp"
#include "Renderer.hpp"
#include "GUI.hpp"

#include "MyTest.hpp"
#include "MyTestClearColor.hpp"
#include "MyTestTexture2D.hpp"
#include "MyTestMesh3D.hpp"
#include "MyTestQuantityGen.hpp"
#include "MyTestOrbitingZoo.hpp"

#include "Camera.hpp"
#include "Cthulhu.hpp"


#ifndef ShaderFile
#define ShaderFile
const std::string SHADER_FILE = "/resources/shaders/Basic.shader";
#endif // !ShaderFile

#ifndef TextureFile
#define TextureFile
const std::string TEXTURE_FILE = "/resources/textures/zote.jpg";
#endif // !TextureFile

#ifndef CthulhuModelFile
#define CthulhuModelFile
const std::string CTHULHU_MODEL_FILE = "/resources/models/Cthulhu.fbx";
#endif // !CthulhuModelFile


Application::Application(const std::string& appPath, int windowWidth, int windowHeight) :
    m_AppPath(appPath), m_AppRunning(true),
    m_Width(windowWidth), m_Height(windowHeight),
    m_Window(NULL), m_Context(NULL),
    m_Clock(nullptr), m_GUI(nullptr), m_Renderer(nullptr)
{
    currentTest = nullptr;
    testMenu = new TestMenu(currentTest);
    currentTest = testMenu;
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
        OnGuiRender();
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

    m_Clock = std::make_shared<Time>();
    m_Renderer = std::make_shared<Renderer>();
    m_GUI = std::make_shared<GUI>(m_Window, m_Context);

    if (!m_GUI->OnInit(m_AppPath)) return false;

    EnableVSync(); 
    m_Renderer->EnableBlending();
    m_Renderer->EnableDepthTest();

    std::cout << "Registering tests : ";
    AppSystemData appSystemData{ m_AppPath, m_Width, m_Height, m_Clock, m_Renderer, m_GUI };
    testMenu->RegisterTest<MyTestClearColor>("Clear Color", appSystemData);
    testMenu->RegisterTest<MyTestTexture2D>("Texture 2D", appSystemData);
    testMenu->RegisterTest<MyTestMesh3D>("Mesh 3D", appSystemData);
    testMenu->RegisterTest<MyTestQuantityGen>("Quantity Generation", appSystemData);
    testMenu->RegisterTest<MyTestOrbitingZoo>("Orbiting Zoo", appSystemData);
    std::cout << std::endl;

    std::cout << "==== END INIT ====" << std::endl;
	return true;
}

void Application::OnEvent(SDL_Event* currentEvent)
{
    m_GUI->OnEvent(currentEvent);
    Inputs::OnEvent(currentEvent);
}

void Application::OnLoop()
{
    m_Clock->Update();
    if (currentTest)
        currentTest->OnLoop(m_Clock->getDeltaTime());
}

void Application::OnRender()
{
    m_Renderer->Clear();
    if (currentTest)
        currentTest->OnRender();
}

void Application::OnGuiRender()
{
    m_GUI->NewFrame();
    if (currentTest) 
    {
        m_GUI->BeginWindow("Tests", 0.0f, 0.0f, 250.0f, 100.0f);
        if (currentTest != testMenu && m_GUI->AddButton("<- Back"))
        {
            delete currentTest;
            currentTest = testMenu;
        }
        currentTest->OnGuiRender();
        m_GUI->EndWindow();
    }
    m_GUI->OnRender();
    SDL_GL_SwapWindow(m_Window);
}

void Application::OnCleanup()
{
    if (currentTest != testMenu)
        delete testMenu;
    delete currentTest;

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

    if (m_Context == NULL)
    {
        std::cout << "ERROR: SDL context creation failed" << std::endl;
        return false;
    }
    if (SDL_GL_MakeCurrent(m_Window, m_Context) < 0)
    {
        std::cout << "ERROR: OpenGL context setup failed" << std::endl;
        return false;
    }

    glViewport(0, 0, m_Width, m_Height);
    glClearColor(0.13f, 0.13f, 0.13f, 0.0f);

    return true;
}

bool Application::InitGlew()
{
    std::cout << "Initializing Glew" << std::endl;
    glewExperimental = true;
    if (glewInit() == GLEW_OK) return true;

    std::cout << "ERROR: Glew init failed" << std::endl;
    return false;
}

void Application::EnableVSync()
{
    SDL_GL_SetSwapInterval(1);
}

//////////////////////////////////////////////////////

void Application::OnQuit()
{
    m_AppRunning = false;
}
