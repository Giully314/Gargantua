/*
* gargantua/core/core_engine.ixx
* 
* PURPOSE: .
* 
* CLASSES:
*	Engine:
* 
* DESCRIPTION:
*
* 
* USAGE:
*/


export module gargantua.core.engine;

import <concepts>;
import <string_view>;

import gargantua.types;
import gargantua.log;
import gargantua.time;
import gargantua.glfw;
import gargantua.app;

namespace gargantua::core
{
	export
	class Engine
	{
	public:
		explicit Engine(const u32 width, const u32 height, const std::string_view title);
		~Engine();

		template <typename T>
			requires std::derived_from<T, app::Application>
		auto CreateApplication()
		{
			// If there is already an application, shutdown it before creating a new one.
			if (application)
			{
				application->Shutdown();
			}

			application = CreateUniqueRes<T>();
		}

		// Game loop
		auto Run() -> void;

		 
	private:
		bool should_close;
		unique_res<app::Application> application;

		time::Stopwatch stopwatch;
		glfw::GLFWSystem glfw_system;
		unique_res<glfw::Window> window;
	};
} // namespace gargantua::core

