/*
* gargantua/platform/platform_system.ixx
* 
* PURPOSE: Initialiaze the resources of platform.
* CLASSES:
* DESCRIPTION:
* 
* TODO: make a platform system with startup, shutdown and update.
* 
*/

module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

export module gargantua.platform.platform_system;

import <string_view>;

import gargantua.types;
import gargantua.platform.event_dispatcher;
import gargantua.platform.platform_events;
import gargantua.platform.window;
import gargantua.platform.keyboard;
import gargantua.platform.key_codes;
import gargantua.platform.mouse;
import gargantua.platform.mouse_codes;


namespace gargantua::platform
{
	export
	struct InitGLFW
	{
		InitGLFW();
		~InitGLFW();
	};


	export 
	class PlatformSystem : public Singleton<PlatformSystem>
	{
	public:

		auto Startup(const u16 width, const u16 height, std::string_view title) -> void;
		
		auto Shutdown() -> void
		{
		}


		auto Run() -> void;


		auto GetWindow() const noexcept -> const Window&
		{
			return *window;
		}

		auto GetWindowProperties() const noexcept -> const WindowProperties&
		{
			return window->GetProperties();
		}
	
	private:
		InitGLFW glfw_init;
		unique_res<Window> window;
	};


} // namespace gargantua::platform
