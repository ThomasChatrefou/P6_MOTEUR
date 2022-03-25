#pragma once

#include <vector>
#include <functional>

class MyTest
{
public:
	MyTest() {}
	virtual ~MyTest() {}

	virtual void OnLoop(float deltaTime) {}
	virtual void OnRender() {}
	virtual void OnGuiRender() {}
};


class TestMenu : public MyTest
{
public:
	TestMenu(MyTest*& currentTestPointer);

	virtual void OnGuiRender() override;
	
	template<typename T>
	void RegisterTest(const std::string& name);

private:
	MyTest*& m_CurrentTest;
	std::vector<std::pair<std::string, std::function<MyTest* ()>>> m_Tests;
};


template<typename T>
void TestMenu::RegisterTest(const std::string& name)
{
	std::cout << "Registering test " << name << std::endl;
	m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
}