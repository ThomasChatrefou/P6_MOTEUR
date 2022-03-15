#pragma once

#include "Includes.hpp"

namespace GC_3D
{

	class Gui
	{
	public:
		Gui();
		~Gui();


	public:
		void OnInit(SDL_Window*, SDL_GLContext);
		void OnEvent(SDL_Event* currentEvent);
		void OnRender();

	public:
		void PrintFPS();
	};
}