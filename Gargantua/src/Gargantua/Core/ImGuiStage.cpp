/*
Gargantua/Core/ImGuiStage.cpp

DESCRIPTION:
	Implementation of the basic setup to make imgui work.
*/
#include "ImGuiStage.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <utility>


namespace Gargantua
{
	namespace Core
	{
		
		ImGuiStage::ImGuiStage(SharedRes<Window> window_) : Stage("ImGuiStage"), window(std::move(window_))
		{
			//Copied from https://github.com/ocornut/imgui/blob/master/examples/example_glfw_opengl3/main.cpp

			// Setup Dear ImGui context
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

			// Setup Dear ImGui style
			ImGui::StyleColorsDark();
			//ImGui::StyleColorsClassic();

			// Setup Platform/Renderer backends
			ImGui_ImplGlfw_InitForOpenGL(window->GetNativeWindow(), true);
			ImGui_ImplOpenGL3_Init("#version 330");
		}


		ImGuiStage::~ImGuiStage()
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}


		void ImGuiStage::Start()
		{
			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}


		void ImGuiStage::End()
		{
			ImGuiIO& io = ImGui::GetIO();
			io.DisplaySize = ImVec2((float)window->GetWidth(), (float)window->GetHeight());

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}


		void ImGuiStage::RenderGUI()
		{

		}


		void ImGuiStage::Execute(const Time::TimeStep&)
		{

		}
	} //namespace Core 
} //namespace Gargantua