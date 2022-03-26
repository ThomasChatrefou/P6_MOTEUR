#pragma once

#include "MyTest.hpp"


class MyTestMesh3D : public MyTest
{
public:
	MyTestMesh3D(const AppSystemData& appData);
	~MyTestMesh3D();

	void OnLoop(float deltaTime) override;
	void OnRender() override;
	void OnGuiRender() override;

private:


};