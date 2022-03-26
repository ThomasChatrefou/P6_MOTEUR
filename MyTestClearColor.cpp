#include "MyTestClearColor.hpp"

#include "OGLIncludes.hpp"
#include "GUI.hpp"
#include "Renderer.hpp"
#include "imgui.h"


MyTestClearColor::MyTestClearColor(const AppSystemData& appData)
	: m_ClearColor{0.2f, 0.3f, 0.8f, 1.0f}
{
	app = appData;
}

MyTestClearColor::~MyTestClearColor() 
{
}

void MyTestClearColor::OnLoop(float deltaTime)
{
}

void MyTestClearColor::OnRender()
{
	glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
	glClear(GL_COLOR_BUFFER_BIT);
}

void MyTestClearColor::OnGuiRender()
{
	app.pGUI->BeginWindow("Debug", 260.0f, 0.0f, 300.0f, 100.0f);
	app.pGUI->AddColorEdit4("Clear Color", m_ClearColor);
	app.pGUI->EndWindow();
}