#pragma once


class MyApp
{
public:
    MyApp();

private:
    uint32_t windowsFlags;
    SDL_Window* win;
    SDL_GLContext context;
    bool apprunning;

public:
    void RunWithCameraMovement();
    void Run();
};