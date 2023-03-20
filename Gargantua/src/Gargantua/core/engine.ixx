/*
* gargantua/core/engine.ixx
* 
* PURPOSE: Glue code for all the submodules.
* 
* CLASSES:
*	Engine: Put together all the submodules and provide the glue code.
* 
* DESCRIPTION:
*	
*/


export module gargantua.core.engine;

import <string_view>;

import gargantua.types;
import gargantua.platform.platform;
import gargantua.log.log;

namespace gargantua::core
{
	export
	class Engine
	{
	public:
		Engine();
		Engine(const u32 width, const u32 height, std::string_view title);


		// Game loop
		auto Run() -> void;


	private:
		auto RegisterListenersToEvents() -> void;
		 
	private:
		platform::InitGLFW glfw_init;
		shared_res<platform::Window> window;
		shared_res<platform::PlatformEventDispatcher> plat_event_dispatcher;

		shared_res<platform::InputSystem> input_peripheral;

		bool should_close;
	};
} // namespace gargantua::core

