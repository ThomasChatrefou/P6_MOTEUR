#pragma once

#include "MyTest.hpp"


class MyTestQuantityGen : public MyTest
{
public:
	MyTestQuantityGen(const AppSystemData& appData);
	~MyTestQuantityGen();

	void OnLoop(float deltaTime) override;
	void OnRender() override;
	void OnGuiRender() override;

private:

};