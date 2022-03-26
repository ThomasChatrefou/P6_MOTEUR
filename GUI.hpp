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
	bool OnInit(const std::string& sourcePath);
	void OnEvent(SDL_Event* currentEvent);
	void NewFrame();
	void OnRender();
	void OnCleanup();

public:
	bool InitStyle(const std::string& sourcePath);
	void PrintFPS(float deltaTime);
	void BeginWindow(const std::string& name, float posX, float posY, float sizeX, float sizeY);
	void EndWindow();

	bool AddButton(const std::string& name);
	bool AddSliderFloat(const std::string& name, float& value, float min, float max);
	bool AddSliderFloat3(const std::string& name, glm::vec3& vector, float min, float max);
	bool AddColorEdit4(const std::string& name, float* colorArray);

public:
	void SpeedSlider(float& speed);
	void Debug(glm::vec3& vector);
	void Tool(bool isActive, float color[4]);
};