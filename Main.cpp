#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif 

#include <gl/GL.h>
#include <SDL.h>

#include "MyApp.h"
#include "Camera.h"


int main(int argc, char* argv[]) 
{
	SDL_Init(SDL_INIT_VIDEO);

    MyApp app1;
    app1.Run();

	return 0;
}