#pragma once

#include "OGLIncludes.hpp"

class GUI
{
public:
	GUI(SDL_Window* window, SDL_GLContext context) : 
		m_Window(window), m_Context(context), pFont(nullptr) {};

	struct ImFont* pFont;

private:
	SDL_Window* m_Window;
	SDL_GLContext m_Context;

public:
	bool OnInit();
	void OnEvent(SDL_Event* currentEvent);
	void NewFrame();
	void OnRender();
	void OnCleanup();

public:
	bool InitStyle();
	void PrintFPS(float deltaTime);
	void BeginWindow(const std::string& name, float posX, float posY, float sizeX, float sizeY);
	void EndWindow();

	void AddSliderFloat(const std::string& name, float& value, float min, float max);
	void AddSliderFloat3(const std::string& name, glm::vec3& vector, float min, float max);

public:
	void SpeedSlider(float& speed);
	void Debug(glm::vec3& vector);
	void Tool(bool isActive, float color[4]);
};