#include "Gui.h"
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>

namespace GC_3D
{
	Gui::~Gui()
	{
	}

	bool Gui::OnInit()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
		io.Fonts->AddFontFromFileTTF("Roboto-Medium.otf", 20.0f);
		ImGui_ImplSDL2_InitForOpenGL(_window, _context);
		ImGui_ImplOpenGL3_Init();

		ImGui::StyleColorsDark();
		return true;
	}

	void Gui::OnEvent(SDL_Event* currentEvent)
	{
		ImGui_ImplSDL2_ProcessEvent(currentEvent);
	}
	
	void Gui::OnLoop()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(_window);
		ImGui::NewFrame();
	}

	void Gui::SpeedSlider(float& speed) 
	{
		ImGui::Begin("SpeedWindow");
		if (ImGui::Button("Reset Speed")) speed = 0;
		ImGui::SliderFloat("Speed", &speed, 0.0f, 10.0f);
		ImGui::End();
	}

	void Gui::Tool(bool isActive, float color[4])
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

	void Gui::OnRender()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Gui::OnCleanup()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void Gui::PrintFPS()
	{
	}
}
