#pragma once

#include "MyTest.hpp"


class MyTestSkyBox : public MyTest
{
public:
	MyTestSkyBox(const AppSystemData& appData);
	~MyTestSkyBox();

	void OnLoop(float deltaTime) override;
	void OnRender() override;
	void OnGuiRender() override;

private:

};