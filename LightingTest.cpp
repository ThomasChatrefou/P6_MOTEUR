#include "LightingTest.hpp"

#include "Time.hpp"
#include "Renderer.hpp"
#include "GUI.hpp"


LightingTest::LightingTest(const AppSystemData& appData)
{
<<<<<<< Updated upstream
    app = appData;

	lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
=======
>>>>>>> Stashed changes
}

LightingTest::~LightingTest()
{
}

void LightingTest::OnLoop(float deltaTime)
{
}

void LightingTest::OnRender()
{
}

void LightingTest::OnGuiRender()
{
<<<<<<< Updated upstream
    app.pGUI->SetFixedWindowSize(250.0f, 100.0f);
    app.pGUI->PrintFPS(app.pClock->getDeltaTime());
    app.pGUI->BeginWindow("Debug", 520.0f, 0.0f, 500.0f, 100.0f);
    app.pGUI->EndWindow();
=======
>>>>>>> Stashed changes
}