#pragma once

#include "MyTest.hpp"


class LightingTest : public MyTest
{
public:
	LightingTest(const AppSystemData& appData);
	~LightingTest();

	void OnLoop(float deltaTime) override;
	void OnRender() override;
	void OnGuiRender() override;

private:
<<<<<<< Updated upstream
	glm::vec3 lightPos;

public:
=======
>>>>>>> Stashed changes

};