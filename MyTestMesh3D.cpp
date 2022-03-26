#include "MyTestMesh3D.hpp"

#include "Time.hpp"
#include "Renderer.hpp"
#include "GUI.hpp"



MyTestMesh3D::MyTestMesh3D(const AppSystemData& appData)
{
    app = appData;
}

MyTestMesh3D::~MyTestMesh3D()
{
}

void MyTestMesh3D::OnLoop(float deltaTime)
{
}

void MyTestMesh3D::OnRender()
{
}

void MyTestMesh3D::OnGuiRender()
{
    app.pGUI->SetFixedWindowSize(250.0f, 100.0f);
    app.pGUI->PrintFPS(app.pClock->getDeltaTime());
    app.pGUI->BeginWindow("Debug", 520.0f, 0.0f, 500.0f, 100.0f);
    app.pGUI->EndWindow();
}