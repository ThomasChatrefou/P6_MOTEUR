#pragma once

#include"gc_3d_defs.hpp"

namespace GC_3D
{
    class MyApp
    {
    public:
        MyApp(int windowWidth, int windowHeight);
        ~MyApp();

    private:
        uint32_t _windowsFlags;
        int _width;
        int _height;
        SDL_Window* _win;
        SDL_GLContext _context;
        bool _appRunning;

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