#include "MyTest.hpp"

#include "imgui.h"


TestMenu::TestMenu(MyTest*& currentTestPointer)
	: m_CurrentTest(currentTestPointer)
{
}

void TestMenu::OnGuiRender()
{
	float headerSize = 33.0f;
	float buttonSize = 27.0f;
	float sizeY = headerSize + buttonSize * m_Tests.size();
	ImGui::SetWindowSize(ImVec2(250.0f, sizeY), ImGuiCond_None);

	for (auto& test : m_Tests)
	{
		if (ImGui::Button(test.first.c_str()))
			m_CurrentTest = test.second();
	}
}
