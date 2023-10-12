/*
* gargantua/platform/platform_system.ixx
* 
* PURPOSE: Initialize the resources of the platform.
* 
* CLASSES:
*	PlatformSystem: Manage all the platform systems.
* 
* DESCRIPTION:
*	Manage the I/O system, event dispatcher, window, thread pool and memory allocators (in future).
* 
* USAGE:
*	Must be used only by the engine.
*/

module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

export module gargantua.platform.platform_system;

import <string_view>;

import gargantua.types;
import gargantua.platform.platform_events;
import gargantua.platform.window;
import gargantua.platform.keyboard;
import gargantua.platform.key_codes;
import gargantua.platform.mouse;
import gargantua.platform.mouse_codes;

import gargantua.app.application;

namespace gargantua::platform
{
	struct InitGLFW
	{
		InitGLFW();
		~InitGLFW();
	};


	export 
	class PlatformSystem : private NonCopyable, NonMovable
	{
	public:
		[[nodiscard]]
		static
		auto Instance() -> PlatformSystem&
		{
			static PlatformSystem sys;
			return sys;
		}

		auto Startup(const u16 width, const u16 height, std::string_view title) -> void;
		
		auto Shutdown() -> void;


		auto Run() -> void;


		auto GetWindow() const noexcept -> const Window&
		{
			return *window;
		}

		auto GetWindowProperties() const noexcept -> const WindowProperties&
		{
			return window->GetProperties();
		}

		
		auto RenderGUI(non_owned_res<app::Application> application) -> void;

	private:
		InitGLFW glfw_init;
		unique_res<Window> window;
	};


} // namespace gargantua::platform
