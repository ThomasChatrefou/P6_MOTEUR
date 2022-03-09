#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif 

#include "gc_3d_defs.hpp"
#include <gl/GL.h>
#include <SDL.h>

#include "MyApp.h"
#include "Camera.h"

using namespace GC_3D;

int main(int argc, char* argv[])
{
	MyApp app1(1024,728);
	app1.Run();

	return 0;
}