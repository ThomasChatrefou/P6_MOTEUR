#include "MyTestClearColor.hpp"

#include "OGLIncludes.hpp"
#include "GUI.hpp"
#include "Renderer.hpp"
#include "imgui.h"


MyTestClearColor::MyTestClearColor(const TestHandlingData& testData)
	: m_ClearColor{0.2f, 0.3f, 0.8f, 1.0f}
{
	data = testData;
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
	data.pGUI->BeginWindow("Debug", 260.0f, 0.0f, 300.0f, 100.0f);
	data.pGUI->AddColorEdit4("Clear Color", m_ClearColor);
	data.pGUI->EndWindow();
}