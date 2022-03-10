#ifdef _WIN32
#include <windows.h>
#endif 

#include <iostream>
#include <gl/GL.h>
#include <SDL.h>
#include <glm/glm.hpp>

#include "MyApp.h"
#include "Geometry.h"
#include "camera.hpp"


namespace GC_3D
{
    MyApp::MyApp(int windowWidth, int windowHeight)
    {
        _appRunning = true;
        _width = windowWidth;
        _height = windowHeight;
        _window = NULL;
        _context = NULL;
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

    bool MyApp::OnInit()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;

        uint32_t windowsFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

        _window = SDL_CreateWindow("MyEngine",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            _width,
            _height,
            windowsFlags);

        if (_window == NULL) return false;

        _context = SDL_GL_CreateContext(_window);

        if (_context == NULL) return false;

        if (SDL_GL_MakeCurrent(_window, _context) < 0) return false;
        
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

    }

    void MyApp::OnRender()
    {
        ResetWindow();

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

        SDL_GL_SwapWindow(_window);
    }

    void MyApp::OnCleanup()
    {
        SDL_Quit();
    }


    void MyApp::Run()
    {
        SDL_Init(SDL_INIT_VIDEO);
        _appRunning = true;
        while (_appRunning)
        {
            DrawTriangleWithMouseMotionEvent();
        }
    }

    void MyApp::DrawTriangleWithMouseMotionEvent()
    {

        SDL_Event curEvent;
        //AddUserEvent();
        SeekForMouseMotionEvent(curEvent);

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

    void MyApp::QuitEvent(SDL_Event& currentEvent)
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

    void MyApp::SeekForMouseMotionEvent(SDL_Event &currentEvent)
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

    void MyApp::ResetWindow() 
    {
        glViewport(0, 0, _width, _height);
        glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void MyApp::RotateCameraAroundOrigin()
    {

        SDL_GL_MakeCurrent(_window, _context);

        SDL_Event curEvent;
        //AddUserEvent();
        SeekForMouseMotionEvent(curEvent);

        ResetWindow();
        



        SDL_GL_SwapWindow(_window);

        vec3 position = vec3(0.0f, 0.0f, 3.0f);
        vec3 target = vec3(0.0f, 0.0f, 0.0f);

        //Camera camera(position, target);
    }

}
