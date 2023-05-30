/*
* gargantua/platform/platform_system.cpp
* 
*
*/
module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>

module gargantua.platform.platform_system;


import gargantua.types;
import gargantua.platform.event_dispatcher;
import gargantua.platform.input_system;
import gargantua.platform.imgui_system;

namespace gargantua::platform
{
	// ************************************* InitGLFW ***************************************************
	
	InitGLFW::InitGLFW()
	{
		bool glfw_initialized = glfwInit();
		if (!glfw_initialized)
		{
			// Log info
			std::exit(EXIT_FAILURE);
		}
	}

	InitGLFW::~InitGLFW()
	{
		glfwTerminate();
	}

	// ************************************* InitGLFW ***************************************************


	// ************************************* PlatformSystem ***************************************************

	auto PlatformSystem::Startup(const u16 width, const u16 height, std::string_view title) -> void
	{
		PlatformEventDispatcher::Instance();
		window = CreateUniqueRes<Window>(width, height, title);
		InputSystem::Instance().Startup();
		ImGuiSystem::Instance().Startup(window.get());
	}

	auto PlatformSystem::Shutdown() -> void
	{
		ImGuiSystem::Instance().Shutdown();
		InputSystem::Instance().Shutdown();
		window.reset();
	}


	auto PlatformSystem::Run() -> void
	{
		InputSystem::Instance().Run();
		window->Update();
	}


	auto PlatformSystem::RenderGUI(non_owned_res<app::Application> application) -> void
	{
		auto& imgui = ImGuiSystem::Instance();
		imgui.BeginScene();
		application->RenderGUI();
		imgui.EndScene();
	}


	// ************************************* PlatformSystem ***************************************************

	

} // namespace gargantua::platform
