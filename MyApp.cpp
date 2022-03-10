#ifdef _WIN32
#include <windows.h>
#endif 

#include <iostream>
#include <gl/GL.h>
#include <SDL.h>
#include <glm/glm.hpp>

#include "MyApp.h"
#include "Camera.h"


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
            vec3(1.0, 0.0, 0.0),
            vec3(0.0, 1.0, 0.0),
            vec3(0.0, 0.0, 0.0),
            vec4(1.0, 1.0, 0.0, 1.0));

        SDL_GL_SwapWindow(_window);
    }

    void MyApp::DrawTriangle(vec3 A, vec3 B, vec3 C, vec4 color)
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
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor4f(1.0, 1.0, 1.0, 1.0);
    }

    void MyApp::RotateCameraAroundOrigin()
    {

        SDL_GL_MakeCurrent(_window, _context);

        SDL_Event curEvent;
        //AddUserEvent();
        SeekForMouseMotionEvent(curEvent);

        ResetWindow();

        DrawTriangle(
            vec3(1.0, 0.0, 0.0),
            vec3(0.0, 1.0, 0.0),
            vec3(0.0, 0.0, 0.0),
            vec4(1.0, 1.0, 0.0, 1.0));
        DrawTriangle(
            vec3(0.0, 1.0, 0.0),
            vec3(0.0, 0.0, 1.0),
            vec3(0.0, 0.0, 0.0),
            vec4(0.0, 1.0, 1.0, 1.0));
        DrawTriangle(
            vec3(0.0, 0.0, 1.0),
            vec3(1.0, 0.0, 0.0),
            vec3(0.0, 0.0, 0.0),
            vec4(1.0, 0.0, 1.0, 1.0));

        SDL_GL_SwapWindow(_window);

        vec3 position = vec3(0.0f, 0.0f, 3.0f);
        vec3 target = vec3(0.0f, 0.0f, 0.0f);

        Camera camera(position, target);
    }

}
