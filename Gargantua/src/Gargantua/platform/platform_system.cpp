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
import gargantua.platform.input_system;

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
		InputSystem::Instance().Startup(&event_dispatcher);
		window = CreateUniqueRes<Window>(width, height, title, &event_dispatcher);
	}


	auto PlatformSystem::Run() -> void
	{
		InputSystem::Instance().Run();
		window->Update();
	}


	// ************************************* PlatformSystem ***************************************************

	

} // namespace gargantua::platform
