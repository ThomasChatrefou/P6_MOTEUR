#pragma once

#include "OGLIncludes.hpp"

class GUI
{
public:
	GUI(SDL_Window* window, SDL_GLContext context) : 
		m_Window(window), m_Context(context), pFont(nullptr) {};

	class ImFont* pFont;

private:
	SDL_Window* m_Window;
	SDL_GLContext m_Context;

public:
	bool OnInit();
	void OnEvent(SDL_Event* currentEvent);
	void OnLoop();
	void OnRender();
	void OnCleanup();

public:
	bool InitStyle();
	void PrintFPS(float deltaTime);
	void SpeedSlider(float& speed);
	void Tool(bool isActive, float color[4]);
};