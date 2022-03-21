#include "MyApp.h"
#include "Geometry.h"
#include "Camera.h"
#include "Cube.h"
#include "Triangle.h"
#include "LoadShader.hpp"
#include "GetAppPath.h"



#ifndef ShadersPath
char* SHADERS_REPOSITORY_NAME = "resources/shaders";
char* VERTEX_SHADERS_FILE_NAME = "SimpleVertexShader.glsl";
char* FRAGMENT_SHADERS_FILE_NAME = "SimpleFragmentShader.glsl";
#endif //ShaderPath


namespace GC_3D
{
    MyApp::MyApp(int windowWidth, int windowHeight)
    {
        _appRunning = true;
        _width = windowWidth;
        _height = windowHeight;
        _window = NULL;
        _context = NULL;
        _programID = 0;
        _matrixID = 0;

        _camera = nullptr;
        _triangle = nullptr;
        _cube = nullptr;
        _mvp = mat4(1.0f);
    }

    int MyApp::OnExecute() 
    {
        if (OnInit() == false)
        {
            return -1;
        }

        SDL_Event currentEvent;

        while (_appRunning)
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


    /***************************
    * game execution functions *
    ***************************/

    bool MyApp::OnInit()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) 
        {
            std::cout << "SDL init failed" << std::endl;
            return false;
        }

        uint32_t windowsFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

        _window = SDL_CreateWindow("MyEngine",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            _width,
            _height,
            windowsFlags);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_PROFILE_CORE);

        if (_window == NULL) 
        {
            std::cout << "SDL window creation failed" << std::endl;
            return false;
        }

        _context = SDL_GL_CreateContext(_window);

        if (_context == NULL)
        {
            std::cout << "SDL context creation failed" << std::endl;
            return false;
        }

        if (SDL_GL_MakeCurrent(_window, _context) < 0)
        {
            std::cout << "OpenGL context setup failed" << std::endl;
            return false;
        }
        
        glewExperimental = true; 
        if (glewInit() != GLEW_OK)
        {
            std::cout << "Glew init failed" << std::endl;
            return false;
        }

        if (!InitCubeScene())
        {
            std::cout << "Scene init failed" << std::endl;
            return false;
        }

        if (!InitShaders())
        {
            std::cout << "Shaders init failed" << std::endl;
            return false;
        }

        

        _start = _clock.now();
        return true;
    }

    void MyApp::OnEvent(SDL_Event* currentEvent)
    {
        if (currentEvent->type == SDL_QUIT)
        {
            _appRunning = false;
        }
    }

    void MyApp::OnLoop()
    {
        //LoopTriangleScene();
        LoopCubeScene();
    }

    void MyApp::OnRender()
    {
        ResetWindow();

        //RenderTriangleScene();
        RenderCubeScene();

        SDL_GL_SwapWindow(_window);
    }

    void MyApp::OnCleanup()
    {
        SDL_Quit();
    }

    bool MyApp::InitShaders()
    {
        std::filesystem::path appPath(GetAppPath());
        auto appDir = appPath.parent_path();
        auto shaderPath = appDir / SHADERS_REPOSITORY_NAME;
        auto vertexShaderPath = shaderPath / VERTEX_SHADERS_FILE_NAME;
        auto fragmentShaderPath = shaderPath / FRAGMENT_SHADERS_FILE_NAME;

        _programID = LoadShaders(vertexShaderPath.string().c_str(), fragmentShaderPath.string().c_str());
        if (_programID == 0) return false;

        _matrixID = glGetUniformLocation(_programID, "MVP");

        return true;
    }

    void MyApp::ResetWindow() 
    {
        glViewport(0, 0, _width, _height);
        glClearColor(0.1f, 0.1f, 0.15f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    /**************************
    * tuto Triangle functions *
    **************************/

    bool MyApp::InitTriangleScene()
    {
        _camera = new Camera();
        _camera->OnInit(
            vec3(4.0f, 3.0f, 3.0f), 
            vec3(0.0f, 0.0f, 0.0f), 
            45.0f, 
            (float)_width / (float)_height, 
            0.1f, 
            100.0f);

        _triangle = new Triangle();
        if (!_triangle->OnInit()) return false;

        GLfloat data[9] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
        };
        _triangle->SetVertex(data);
        _triangle->SetBuffer();
        _triangle->SetModelMatrix(mat4(1.0f));

        mat4 proj = _camera->GetProjectionMatrix();
        mat4 view = _camera->GetLookAtMatrix();
        mat4 model = _triangle->GetModelMatrix();
        _mvp = proj * view * model;

        return true;
    }

    void MyApp::LoopTriangleScene()
    {
        _triangle->OnLoop();
        glUniformMatrix4fv(_matrixID, 1, GL_FALSE, &_mvp[0][0]);

    }
    
    void MyApp::RenderTriangleScene()
    {
        glUseProgram(_programID);
        _triangle->OnRender();
    }

    /**************************
    *    tuto Cube function   *
    **************************/

    bool MyApp::InitCubeScene()
    {
        _camera = new Camera();
        _camera->OnInit(
            vec3(4.0f, 3.0f, 3.0f),
            vec3(0.0f, 0.0f, 0.0f),
            45.0f,
            (float)_width / (float)_height,
            0.1f,
            100.0f);

        _cube = new Cube();
        if (!_cube->OnInit()) return false;
        
        _cube->SetModelMatrix(mat4(1.0f));

        mat4 proj = _camera->GetProjectionMatrix();
        mat4 view = _camera->GetLookAtMatrix();
        mat4 model = _cube->GetModelMatrix();
        _mvp = proj * view * model;

        return true;
    }

    void MyApp::LoopCubeScene()
    {
        _cube->OnLoop();
        glUniformMatrix4fv(_matrixID, 1, GL_FALSE, &_mvp[0][0]);

    }

    void MyApp::RenderCubeScene()
    {
        glUseProgram(_programID);
        _cube->OnRender();
    }


    /***********************
    * old openGL functions *
    ***********************/

    void MyApp::DrawRotatingCube() 
    {
        vec4 A = vec4(1.0, 0.0, 0.0, 1.0);
        vec4 B = vec4(0.0, 1.0, 0.0, 1.0);
        vec4 C = vec4(0.0, 0.0, 0.0, 1.0);

        mat4 model = mat4(1.0f);
        mat4 view = mat4(1.0f);
        mat4 proj = mat4(1.0f);
        
        auto now = _clock.now();
        Duration timeStep = now - _start;
        vec3 viewPos = vec3(0.5 + 3.0 * sin(timeStep.count() * 1E-9), 2.0, 0.5 + 3.0 * cos(timeStep.count() * 1E-9));

        model = rotate(model, radians(45.0f), vec3(0.0f, 0.0f, 1.0f));
        view = lookAt(viewPos, vec3(0.5f,0.5f,0.5f), vec3(0.0f, 1.0f, 0.0f));
        proj = perspective(radians(45.0f), (float)_width / (float)_height, 0.1f, 10.0f);
     

        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(value_ptr(proj));

        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(value_ptr(view));

        //glMultMatrixf(value_ptr(model));

        vec4 color = vec4(1.0, 1.0, 0.0, 1.0);

        Geometry geo;
        geo.m_Pos =
        {
            vec3(0.0, 0.0, 0.0),
            vec3(0.0, 0.0, 1.0),
            vec3(0.0, 1.0, 0.0),
            vec3(0.0, 1.0, 1.0),
            vec3(1.0, 0.0, 0.0),
            vec3(1.0, 0.0, 1.0),
            vec3(1.0, 1.0, 0.0),
            vec3(1.0, 1.0, 1.0)
        };

        geo.m_Indices =
        {
            3,1,2,
            0,2,1,
            4,6,0,
            2,0,6,
            5,4,7,
            6,7,4,
            3,5,7,
            5,3,1,
            2,6,3,
            7,3,6,
            0,4,1,
            5,1,4
        };
        glEnable(GL_CULL_FACE);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        geo.Bind();
        geo.Draw();
    }

    void MyApp::DrawTriangleWithMouseMotionEvent()
    {

        SDL_Event curEvent;
        //AddUserEvent();
        OnMouseTrackingEvent(curEvent);

        ResetWindow();

        DrawTriangle(
            vec4(1.0, 0.0, 0.0, 1.0),
            vec4(0.0, 1.0, 0.0, 1.0),
            vec4(0.0, 0.0, 0.0, 1.0),
            vec4(1.0, 1.0, 0.0, 1.0));

        SDL_GL_SwapWindow(_window);
    }

    void MyApp::DrawTriangle(vec4 A, vec4 B, vec4 C, vec4 color)
    {
        glBegin(GL_TRIANGLES);
        glColor4f(color.r, color.g, color.b, color.a);
        glVertex3f(A.x, A.y, A.z);
        glVertex3f(B.x, B.y, B.z);
        glVertex3f(C.x, C.y, C.z);
        glEnd();
    }

    void MyApp::AddUserEvent()
    {
        SDL_Event user_event;
        user_event.type = SDL_USEREVENT;
        user_event.user.code = 2;
        user_event.user.data1 = NULL;
        user_event.user.data2 = NULL;
        SDL_PushEvent(&user_event);
    }

    void MyApp::OnMouseTrackingEvent(SDL_Event& currentEvent)
    {
        while (SDL_PollEvent(&currentEvent))
        {
            switch (currentEvent.type)
            {
            case SDL_MOUSEMOTION:
                printf("Current mouse position is: (%d, %d)\n", currentEvent.motion.x, currentEvent.motion.y);
                break;

            default:
                printf("Unhandled Event!\n");
                break;
            }
        }
    }
}