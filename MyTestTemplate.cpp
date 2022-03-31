#include "MyTestTemplate.hpp"

#include "Time.hpp"
#include "Renderer.hpp"
#include "GUI.hpp"


MyTestTemplate::MyTestTemplate(const AppSystemData& appData)
{
    app = appData;
}

MyTestTemplate::~MyTestTemplate()
{
}

void MyTestTemplate::OnLoop(float deltaTime)
{
}

void MyTestTemplate::OnRender()
{
}

void MyTestTemplate::OnGuiRender()
{
    app.pGUI->SetFixedWindowSize(250.0f, 100.0f);
    app.pGUI->PrintFPS(app.pClock->getDeltaTime());
    app.pGUI->BeginWindow("Debug", 520.0f, 0.0f, 500.0f, 100.0f);
    app.pGUI->EndWindow();
}