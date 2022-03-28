#pragma once

#include "MyTest.hpp"


class MyTestTemplate : public MyTest
{
public:
	MyTestTemplate(const AppSystemData& appData);
	~MyTestTemplate();

	void OnLoop(float deltaTime) override;
	void OnRender() override;
	void OnGuiRender() override;

private:

};