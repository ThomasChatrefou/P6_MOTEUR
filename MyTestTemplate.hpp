#pragma once

#include "MyTest.hpp"

class MyTestTemplate : public MyTest
{
public:
	MyTestTemplate();
	~MyTestTemplate();

	void OnLoop(float deltaTime) override;
	void OnRender() override;
	void OnGuiRender() override;

private:


};