#include "Gui.h"
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>

namespace GC_3D
{
	Gui::Gui()
	{
	}

	Gui::~Gui()
	{
	}

	void Gui::OnInit(SDL_Window* win, SDL_GLContext context)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

		ImGui_ImplSDL2_InitForOpenGL(win, context);
		ImGui_ImplOpenGL3_Init();

		ImGui::StyleColorsDark();
	}

	void Gui::OnEvent(SDL_Event* currentEvent)
	{
		
	}

	void Gui::OnRender()
	{
	}

	void Gui::PrintFPS()
	{
	}
}
