#include "MyApp.h"
#include "Geometry.h"
#include "Camera.h"
#include "Triangle.h"
#include "Cube.h"
#include "shaders/LoadShader.hpp"
#include "GetAppPath.h"
#include "Gui.h"


#ifndef ShadersPath
char* SHADERS_REPOSITORY_NAME = "shaders";
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
        _mvpTriangle = mat4(1.0f);
        _mvpCube = mat4(1.0f);

        _gui = nullptr;
        _speed = 0.5f;
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

        // Permet d'utiliser renderProfile
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

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

        if (!InitScene())
        {
            std::cout << "Scene init failed" << std::endl;
            return false;
        }

        if (!InitShaders())
        {
            std::cout << "Shaders init failed" << std::endl;
            return false;
        }

        _gui = new Gui(_window, _context);
        if (!_gui->OnInit())
        {
            std::cout << "GUI init failed" << std::endl;
            return false;
        }

        _start = _clock.now();
        return true;
    }

    void MyApp::OnEvent(SDL_Event* currentEvent)
    {
        _gui->OnEvent(currentEvent);
        if (currentEvent->type == SDL_QUIT)
        {
            _appRunning = false;
        }
    }

    void MyApp::OnLoop()
    {
        _gui->OnLoop();
        _gui->SpeedSlider(_speed);
        bool isActive = true;
        float color[4] {0.0f,0.0f,0.0f,1.0f};
        _gui->Tool(isActive, color);
        LoopScene();
    }

    void MyApp::OnRender()
    {
        ResetWindow();

        _gui->OnRender();

        RenderScene();

        SDL_GL_SwapWindow(_window);
    }

    void MyApp::OnCleanup()
    {
        _gui->OnCleanup();
        SDL_Quit();
    }


    /*****************
    * tuto functions *
    *****************/

    bool MyApp::InitScene()
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

        GLfloat trianglePositionData[] = {
            -2.0f, -2.0f, 2.0f,
            1.0f, -2.0f, 2.0f,
            0.0f,  2.0f, 1.0f,
        };
        GLfloat triangleColorData[9];

        srand((unsigned)time(NULL));
        for (int i = 0; i < 9; ++i) triangleColorData[i] = (float)rand() / RAND_MAX;

        _triangle->SetVertex(trianglePositionData);
        _triangle->SetColor(triangleColorData);
        _triangle->SetBuffer();
        _triangle->SetModelMatrix(mat4(1.0f));
        
        mat4 proj = _camera->GetProjectionMatrix();
        mat4 view = _camera->GetLookAtMatrix();
        mat4 model = _triangle->GetModelMatrix();
        _mvpTriangle = proj * view * model;


        _cube = new Cube();
        if (!_cube->OnInit()) return false;

        GLfloat cubePositionData[] = {
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, 
            1.0f, 1.0f,-1.0f, 
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f, 
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
        };
        GLfloat cubeColorData[] = {
            0.583f,  0.771f,  0.014f,
            0.609f,  0.115f,  0.436f,
            0.327f,  0.483f,  0.844f,
            0.822f,  0.569f,  0.201f,
            0.435f,  0.602f,  0.223f,
            0.310f,  0.747f,  0.185f,
            0.597f,  0.770f,  0.761f,
            0.559f,  0.436f,  0.730f,
            0.359f,  0.583f,  0.152f,
            0.483f,  0.596f,  0.789f,
            0.559f,  0.861f,  0.639f,
            0.195f,  0.548f,  0.859f,
            0.014f,  0.184f,  0.576f,
            0.771f,  0.328f,  0.970f,
            0.406f,  0.615f,  0.116f,
            0.676f,  0.977f,  0.133f,
            0.971f,  0.572f,  0.833f,
            0.140f,  0.616f,  0.489f,
            0.997f,  0.513f,  0.064f,
            0.945f,  0.719f,  0.592f,
            0.543f,  0.021f,  0.978f,
            0.279f,  0.317f,  0.505f,
            0.167f,  0.620f,  0.077f,
            0.347f,  0.857f,  0.137f,
            0.055f,  0.953f,  0.042f,
            0.714f,  0.505f,  0.345f,
            0.783f,  0.290f,  0.734f,
            0.722f,  0.645f,  0.174f,
            0.302f,  0.455f,  0.848f,
            0.225f,  0.587f,  0.040f,
            0.517f,  0.713f,  0.338f,
            0.053f,  0.959f,  0.120f,
            0.393f,  0.621f,  0.362f,
            0.673f,  0.211f,  0.457f,
            0.820f,  0.883f,  0.371f,
            0.982f,  0.099f,  0.879f
        };

        _cube->SetVertex(cubePositionData);
        _cube->SetColor(cubeColorData);
        _cube->SetBuffer();
        _cube->SetModelMatrix(mat4(1.0f));

        model = _cube->GetModelMatrix();
        _mvpCube = proj * view * model;

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        return true;
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

    void MyApp::LoopScene()
    {
        _triangle->OnLoop();
        _cube->OnLoop();
        glUniformMatrix4fv(_matrixID, 1, GL_FALSE, &_mvpTriangle[0][0]);

    }

    void MyApp::RenderScene()
    {
        glUseProgram(_programID);
        _triangle->OnRender();
        _cube->OnRender();
        
        Timestamp now = _clock.now();
        Duration timeStep = now - _start;
        vec3 viewPos = vec3(5.0 * sin(Seconds(timeStep) * _speed), 3.0, 5.0 * cos(Seconds(timeStep) * _speed));
        _camera->SetPosition(viewPos);

        mat4 proj = _camera->GetProjectionMatrix();
        mat4 view = _camera->GetLookAtMatrix();
        mat4 model = _cube->GetModelMatrix();
        _mvpTriangle = proj * view * model;

        model = _cube->GetModelMatrix();
        _mvpCube = proj * view * model;
    }

    void MyApp::ResetWindow() 
    {
        glViewport(0, 0, _width, _height);
        glClearColor(0.1f, 0.1f, 0.15f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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