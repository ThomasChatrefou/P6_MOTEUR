#ifdef _WIN32
#include <windows.h>
#endif 

#include <iostream>
#include <gl/GL.h>
#include <SDL.h>
#include <glm/glm.hpp>

#include "MyApp.h"
#include "Camera.h"


MyApp::MyApp()
{
    windowsFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

    win = SDL_CreateWindow("MyEngine",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        768,
        windowsFlags);

    context = SDL_GL_CreateContext(win);

    apprunning = false;
}

void MyApp::RunWithCameraMovement() 
{
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);

    Camera camera(position, target);
}

void MyApp::Run()
{
    apprunning = true;
    while (apprunning)
    {
        SDL_GL_MakeCurrent(win, context);
        SDL_Event curEvent;

        SDL_Event user_event;
        user_event.type = SDL_USEREVENT;
        user_event.user.code = 2;
        user_event.user.data1 = NULL;
        user_event.user.data2 = NULL;
        SDL_PushEvent(&user_event);

        while (SDL_PollEvent(&curEvent))
        {
            switch (curEvent.type)
            {
            case SDL_MOUSEMOTION:
                printf("We got a motion event.\n");
                printf("Current mouse position is: (%d, %d)\n", curEvent.motion.x, curEvent.motion.y);
                break;

            default:
                printf("Unhandled Event!\n");
                break;
            }
        }
        glViewport(0, 0, 1024, 768);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBegin(GL_TRIANGLES);
        glVertex3f(-1.0, 0.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);

        glEnd();

        SDL_GL_SwapWindow(win);
    }
}
