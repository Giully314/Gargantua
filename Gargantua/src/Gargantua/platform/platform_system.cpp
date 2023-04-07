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
		input_system.Startup(&event_dispatcher);
		window = CreateUniqueRes<Window>(width, height, title, &event_dispatcher);
	}


	auto PlatformSystem::Run() -> void
	{
		input_system.Run();
		window->Update();
	}


	// ************************************* PlatformSystem ***************************************************

	

} // namespace gargantua::platform
