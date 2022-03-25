#include "MyTest.hpp"

#include "imgui.h"


TestMenu::TestMenu(MyTest*& currentTestPointer)
	: m_CurrentTest(currentTestPointer)
{
}

void TestMenu::OnGuiRender()
{
	for (auto& test : m_Tests)
	{
		if (ImGui::Button(test.first.c_str()))
			m_CurrentTest = test.second();
	}
}
