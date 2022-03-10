#pragma once

#include"gc_3d_defs.hpp"

namespace GC_3D
{
    class MyApp
    {
    private:
        bool _appRunning;
        int _width;
        int _height;
        SDL_Window* _window;
        SDL_GLContext _context;

    public:
        MyApp(int windowWidth, int windowHeight);
        
        int OnExecute();

    public:
        bool OnInit();
        void OnEvent(SDL_Event* currentEvent);
        void OnLoop();
        void OnRender();
        void OnCleanup();

    public:
        void Run();

        void DrawTriangleWithMouseMotionEvent();
        void AddUserEvent();
        void QuitEvent(SDL_Event& currentEvent);
        void SeekForMouseMotionEvent(SDL_Event &currentEvent);
        void ResetWindow();
        void DrawTriangle(vec3 A, vec3 B, vec3 C, vec4 color);

        void RotateCameraAroundOrigin();
    };
}