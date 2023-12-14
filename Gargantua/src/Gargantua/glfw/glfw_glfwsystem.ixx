/*
* gargantua/glfw/glfw_glfwsystem.ixx
* 
* PURPOSE: handle glfw.
* 
* CLASSES:
*	GLFWSystem: Startup and shutdown the glfw library.
* 
* TODO:
*	hide this component from user.
* 
*/
module;

#include <gargantua/log/logger_macro.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

export module gargantua.glfw.glfw_system;

import <cstdlib>;

import gargantua.types;
import gargantua.log;

namespace gargantua::glfw
{
	export class GLFWSystem : NonCopyable, NonMovable
	{
	public:
		/*
		* Start the glfw library.
		*/
		auto Startup() -> void
		{
			GRG_CORE_DEBUG("GLFWSystem startup");
			auto glfw_initialized = glfwInit();
			if (glfw_initialized == GLFW_FALSE)
			{
				GRG_CORE_ERROR("Error while initializing GLFW");
				// Exit failure
				std::exit(1); 
			}
		}

		
		/*
		* Terminate the glfw library.
		*/
		auto Shutdown() -> void
		{
			GRG_CORE_DEBUG("GLFWSystem shutdown");
			glfwTerminate();
		}
	};
} // namespace gargantua::glfw