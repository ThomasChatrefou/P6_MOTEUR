#include "GUI.hpp"
#include "GetAppPath.hpp"

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>


#ifndef FontsPath
const char* FONTS_REPOSITORY_NAME = "../source/dep/imgui/misc/fonts";
const char* FONT_FILE_NAME = "Karla-Regular.ttf";
#endif //FontsPath


bool GUI::OnInit()
{
	std::cout << "Initializing GUI" << std::endl;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// if (!InitStyle()) return false;

	if (!ImGui_ImplSDL2_InitForOpenGL(m_Window, m_Context))
	{
		std::cout << "ERROR: ImGui_ImplSDL2 init failed" << std::endl;
		return false;
	}

	if (!ImGui_ImplOpenGL3_Init()) 
	{
		return false;
		std::cout << "ERROR: ImGui_ImplOpenGL3 init failed" << std::endl;
	}

	ImGui::StyleColorsDark();

	return true;
}

void GUI::OnEvent(SDL_Event* currentEvent)
{
	ImGui_ImplSDL2_ProcessEvent(currentEvent);
}

void GUI::NewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();
}

void GUI::OnRender()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::OnCleanup()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

///////////////////////////////////////////////////////

bool GUI::InitStyle()
{
	ImGui::StyleColorsDark();

	std::filesystem::path appPath(GetAppPath());
	auto appDir = appPath.parent_path();
	auto fontsPath = appDir / FONTS_REPOSITORY_NAME;
	auto fontPath = fontsPath / FONT_FILE_NAME;

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	pFont = io.Fonts->AddFontFromFileTTF(fontPath.string().c_str(), 18.0f);

	if (pFont != NULL) return true;
	std::cout << "ERROR: font file not found" << std::endl;
	return false;
}

void GUI::PrintFPS(float deltaTime)
{
	ImGui::Begin("Perfs");
	ImGui::SetWindowPos(ImVec2(10, 10), ImGuiCond_Once);
	ImGui::SetWindowSize(ImVec2(300, 100), ImGuiCond_Once);
	ImGui::Text("Frame Duration (ms) : %5.2f", deltaTime * 1e3);
	ImGui::Text("FPS : %5.0f", 1.0 / deltaTime);
	ImGui::End();
}

void GUI::BeginWindow(const std::string& name, float posX, float posY, float sizeX, float sizeY)
{
	ImGui::Begin(name.c_str());
	ImGui::SetWindowPos(ImVec2(posX, posY), ImGuiCond_Once);
	ImGui::SetWindowSize(ImVec2(sizeX, sizeY), ImGuiCond_Once);
}

void GUI::EndWindow() 
{
	ImGui::End();
}

void GUI::AddSliderFloat(const std::string& name, float& value, float min, float max)
{
	ImGui::SliderFloat(name.c_str(), &value, min, max);
}

void GUI::AddSliderFloat3(const std::string& name, glm::vec3& vector, float min, float max)
{
	ImGui::SliderFloat3(name.c_str(), &vector.x, min, max);
}

void GUI::SpeedSlider(float& speed)
{
	ImGui::Begin("SpeedWindow");
	if (ImGui::Button("Reset Speed")) speed = 0;
	ImGui::SliderFloat("Speed", &speed, 0.0f, 10.0f);
	ImGui::End();
}

void GUI::Debug(glm::vec3& vector)
{
	ImGui::Begin("Debug");
	ImGui::SetWindowPos(ImVec2(320, 10), ImGuiCond_Once);
	ImGui::SetWindowSize(ImVec2(600, 100), ImGuiCond_Once);
	ImGui::End();
}


void GUI::Tool(bool isActive, float color[4])
{// Create a window called "My First Tool", with a menu bar.
	ImGui::Begin("My First Tool", &isActive, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Close", "Ctrl+W")) { isActive = false; }
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	// Edit a color (stored as ~4 floats)
	ImGui::ColorEdit4("Color", color);

	// Plot some values
	const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
	ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

	// Display contents in a scrolling region
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
	ImGui::BeginChild("Scrolling");
	for (int n = 0; n < 10; n++)
		ImGui::Text("%04d: Some text", n);
	ImGui::EndChild();
	ImGui::End();

}