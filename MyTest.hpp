#pragma once

class MyTest
{
public:
	MyTest() {}
	virtual ~MyTest();

	virtual void OnLoop(float deltaTime) {}
	virtual void OnRender() {}
	virtual void OnGuiRender() {}
};