#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <SDL.h>

class Time;
class GUI;
class Renderer;

struct TestHandlingData 
{
	std::string srcPath;
	int winWidth = 0;
	int winHeight = 0;

	std::shared_ptr<Time> pClock;
	std::shared_ptr<GUI> pGUI;
	std::shared_ptr<Renderer> pRenderer;
};


class MyTest
{
public:
	MyTest() {}
	virtual ~MyTest() {}

	virtual void OnLoop(float deltaTime) {}
	virtual void OnRender() {}
	virtual void OnGuiRender() {}

protected:
	TestHandlingData data;
};


class TestMenu : public MyTest
{
public:
	TestMenu(MyTest*& currentTestPointer);

	virtual void OnGuiRender() override;
	
	template<typename T>
	void RegisterTest(const std::string& name, const TestHandlingData& testData);

private:
	MyTest*& m_CurrentTest;
	std::vector<std::pair<std::string, std::function<MyTest* ()>>> m_Tests;
};


template<typename T>
void TestMenu::RegisterTest(const std::string& name, const TestHandlingData& testData)
{
	std::cout << "Registering test " << name << std::endl;
	m_Tests.push_back(std::make_pair(name, [testData]() { return new T(testData); }));
}