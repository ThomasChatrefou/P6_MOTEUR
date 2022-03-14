#pragma once

#include "Includes.hpp"

namespace GC_3D
{
    class Camera;
    class Triangle;
    class Cube;

    class MyApp
    {
    public:
        MyApp(int windowWidth, int windowHeight);
        
        int OnExecute();

    private:
        bool _appRunning;
        int _width;
        int _height;
        SDL_Window* _window;
        SDL_GLContext _context;
        GLuint _programID;
        GLuint _matrixTriangleID;
        GLuint _matrixCubeID;

        Clock _clock;
        Timestamp _start;

        Camera* _camera;
        Triangle* _triangle;
        Cube* _cube;

        mat4 _mvpTriangle;
        mat4 _mvpCube;

    public: // game execution functions
        bool OnInit();
        void OnEvent(SDL_Event* currentEvent);
        void OnLoop();
        void OnRender();
        void OnCleanup();

    public: // tuto functions
        bool InitScene();
        bool InitShaders();
        void LoopScene();
        void RenderScene();
        void ResetWindow();

    public: // old openGL functions
        void DrawRotatingCube();
        void DrawTriangleWithMouseMotionEvent();
        void DrawTriangle(vec4 A, vec4 B, vec4 C, vec4 color);
        void AddUserEvent();
        void OnMouseTrackingEvent(SDL_Event& currentEvent);
    };
}