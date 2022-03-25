#include "Application.hpp"
#include "GUI.hpp"
#include "Time.hpp"
#include "Renderer.hpp"

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include "Shader.hpp"
#include "MyTexture.hpp"

#include "Camera.hpp"
#include "Cthulhu.hpp"

#include "MyTest.hpp"
#include "MyTestClearColor.hpp"
#include "imgui.h"


const std::string SHADER_FILE = "resources/shaders/Basic.shader";
const std::string TEXTURE_FILE = "resources/textures/zote.jpg";
const std::string CTHULHU_MODEL_FILE = "resources/models/Cthulhu.fbx";



Application::Application(const std::string& sourcePath, int windowWidth, int windowHeight) :
    m_SourcePath(sourcePath), m_AppRunning(true),
    m_Width(windowWidth), m_Height(windowHeight),
    m_Window(NULL), m_Context(NULL),
    m_Clock(nullptr), m_GUI(nullptr), m_Renderer(nullptr)
{
    //temp
    translationA = glm::vec3(0.0f);
    translationB = glm::vec3(0.0f);
    va = nullptr;
    vb = nullptr;
    ib = nullptr;
    shader = nullptr;
    texture = nullptr;
    cam = nullptr;
    cthulhu = nullptr;
    
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
    m_GUI = new GUI(m_Window, m_Context);
    if (!m_GUI->OnInit()) return false;

    EnableVSync(); 
    EnableBending();

    m_Renderer = new Renderer();

    testMenu->RegisterTest<MyTestClearColor>("Clear Color");

    // squares
    /*
    float positions[] = {
        -100.0f, -100.0f, 0.0f, 0.0f,
         100.0f, -100.0f, 1.0f, 0.0f,
         100.0f,  100.0f, 1.0f, 1.0f,
        -100.0f,  100.0f, 0.0f, 1.0f,
    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    translationA = glm::vec3(200.0f, 200.0f, 0.0f);
    translationB = glm::vec3(400.0f, 200.0f, 0.0f);


    va = new VertexArray();

    vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push(2);
    layout.Push(2);

    va->AddBuffer(*vb, layout);

    ib = new IndexBuffer(indices, 6);

    auto shaderPath = m_SourcePath + SHADER_FILE;
    shader = new Shader(shaderPath);

    auto texturePath = m_SourcePath + TEXTURE_FILE;
    texture = new MyTexture(texturePath);
    texture->Bind();
    shader->SetUniform1i("u_Texture", 0);

    va->Unbind();
    vb->Unbind();
    ib->Unbind();
    shader->Unbind();
    */

    // cthulhu
    /*
    { 
        //temp -> put this into scene
        glm::vec3 camPos = glm::vec3(0.0f, 0.0f, -3.0f);
        glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
        float fov = 45.0f;

        cam = new Camera();
        cam->OnInit(camPos, target, fov, (float)m_Width / (float)m_Height, 0.1f, 100.0f);

        cthulhu = new Cthulhu();
        cthulhu->OnInit(CTHULHU_MODEL_PATH);
    

        glm::mat4 proj = cam->GetProjectionMatrix();
        glm::mat4 view = cam->GetLookAtMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 _mvp = proj * view * model;

    }
    */


    m_Clock = new Time();

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
    m_Clock->OnLoop();
}

void Application::OnRender()
{
    m_Renderer->Clear();

    //  RENDERING STUFF

    // squares
    /*
    m_GUI->BeginWindow("Debug", 320.0f, 10.0f, 600.0f, 100.0f);

    glm::mat4 proj = glm::ortho(0.0f, (float)m_Width, 0.0f, (float)m_Height, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
        glm::mat4 mvp = proj * view * model;
        shader->Bind();
        shader->SetUniformMat4f("u_MVP", mvp);
        m_Renderer->Draw(*va, *ib, *shader);
    }

    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
        glm::mat4 mvp = proj * view * model;
        shader->Bind();
        shader->SetUniformMat4f("u_MVP", mvp);
        m_Renderer->Draw(*va, *ib, *shader);
    }

    */

    //  END RENDERING

}

void Application::OnGuiRender()
{
    m_GUI->NewFrame();

    // GUI RENDERING

    if (currentTest) 
    {
        currentTest->OnLoop(m_Clock->getDeltaTime());
        currentTest->OnRender();
        ImGui::Begin("Test");
        if (currentTest != testMenu && ImGui::Button("<-"))
        {
            delete currentTest;
            currentTest = testMenu;
        }
        currentTest->OnGuiRender();
        ImGui::End();
    }


    /*
    m_GUI->BeginWindow("Debug", 320.0f, 10.0f, 600.0f, 100.0f);
    m_GUI->AddSliderFloat3("TranslationB", translationB, 0.0f, 1000.0f);
    m_GUI->AddSliderFloat3("TranslationA", translationA, 0.0f, 1000.0f);
    m_GUI->EndWindow();
    m_GUI->PrintFPS(m_Clock->getDeltaTime());
    */

    m_GUI->OnRender();

    // END GUI RENDERING

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

void Application::EnableBending()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//////////////////////////////////////////////////////

void Application::OnQuit()
{
    m_AppRunning = false;
}
