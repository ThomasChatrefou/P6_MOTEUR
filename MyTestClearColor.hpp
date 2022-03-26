#pragma once

#include "MyTest.hpp"

class MyTestClearColor : public MyTest
{
public:
	MyTestClearColor(const TestHandlingData& testData);
	~MyTestClearColor();

	void OnLoop(float deltaTime) override;
	void OnRender() override;
	void OnGuiRender() override;

private:
	float m_ClearColor[4];

};