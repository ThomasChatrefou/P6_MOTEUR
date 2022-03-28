#pragma once

#include <memory>
#include <vector>
#include <functional>


class Time;
class Renderer;
class GUI;


struct AppSystemData 
{
	std::string srcPath;
	int winWidth = 0;
	int winHeight = 0;

	std::shared_ptr<Time> pClock;
	std::shared_ptr<Renderer> pRenderer;
	std::shared_ptr<GUI> pGUI;
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
	AppSystemData app;
};


class TestMenu : public MyTest
{
public:
	TestMenu(MyTest*& currentTestPointer);

	virtual void OnGuiRender() override;
	
	template<typename T>
	void RegisterTest(const std::string& name, const AppSystemData& testData);

private:
	MyTest*& m_CurrentTest;
	std::vector<std::pair<std::string, std::function<MyTest* ()>>> m_Tests;
};


template<typename T>
void TestMenu::RegisterTest(const std::string& name, const AppSystemData& appData)
{
	std::cout << " " << name << " ";
	m_Tests.push_back(std::make_pair(name, [appData]() { return new T(appData); }));
}