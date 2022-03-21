#pragma once

#include "Includes.hpp"

namespace GC_3D
{

	class Gui
	{
	public:
		Gui(SDL_Window* window, SDL_GLContext context) : _window(window), _context(context) {};
		~Gui();

	private:
		SDL_Window* _window;
		SDL_GLContext _context;


	public:
		bool OnInit();
		void OnEvent(SDL_Event* currentEvent);
		void OnLoop();
		void OnRender();
		void OnCleanup();

	public:
		void Tool(bool isActive, float color[4]);
		void SpeedSlider(float& speed);
		void PrintFPS();
	};
}