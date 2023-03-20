/*
* gargantua/platform/platform_init.cpp
* (The name of the file is temporary)
*
*/
module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>

module gargantua.platform.platform_manager;


import gargantua.types;


namespace gargantua::platform
{
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

} // namespace gargantua::platform
