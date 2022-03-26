#include "MyTestTemplate.hpp"

#include "OGLIncludes.hpp"
#include "Renderer.hpp"
#include "imgui.h"


MyTestTemplate::MyTestTemplate()
{
}

MyTestTemplate::~MyTestTemplate()
{
}

void MyTestTemplate::OnLoop(float deltaTime)
{
}

void MyTestTemplate::OnRender()
{
	glClearColor(0.13f, 0.13f, 0.13f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void MyTestTemplate::OnGuiRender()
{
}