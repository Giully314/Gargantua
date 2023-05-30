/*
* gargantua/platform/imgui_system.cpp
*/

module;

#include "../vendor/glfw/include/GLFW/glfw3.h"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


module gargantua.platform.imgui_system;


namespace gargantua::platform
{
	auto ImGuiSystem::Startup(non_owned_res<Window> window) -> void
	{
		this->window = window;

		//Copied from https://github.com/ocornut/imgui/blob/master/examples/example_glfw_opengl3/main.cpp

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		  //
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window->GetNative(), true);
		ImGui_ImplOpenGL3_Init("#version 450");
	}


	auto ImGuiSystem::Shutdown() -> void
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}


	auto ImGuiSystem::BeginScene() -> void
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}


	auto ImGuiSystem::EndScene() -> void
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)window->GetWidth(), (float)window->GetHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

} // namespace gargantua::platform
