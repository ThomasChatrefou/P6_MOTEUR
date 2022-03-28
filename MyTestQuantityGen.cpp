#include "MyTestQuantityGen.hpp"

#include "Time.hpp"
#include "Renderer.hpp"
#include "GUI.hpp"


MyTestQuantityGen::MyTestQuantityGen(const AppSystemData& appData)
{
    app = appData;
}

MyTestQuantityGen::~MyTestQuantityGen()
{
}

void MyTestQuantityGen::OnLoop(float deltaTime)
{
}

void MyTestQuantityGen::OnRender()
{
}

void MyTestQuantityGen::OnGuiRender()
{
    app.pGUI->SetFixedWindowSize(250.0f, 100.0f);
    app.pGUI->PrintFPS(app.pClock->getDeltaTime());
    app.pGUI->BeginWindow("Debug", 520.0f, 0.0f, 500.0f, 100.0f);
    app.pGUI->EndWindow();
}