/*
* gargantua/core/engine.ixx
* 
* PURPOSE: Glue code for all the modules.
* 
* CLASSES:
*	Engine: Orchestrate all the modules to work together and in order.
* 
* DESCRIPTION:
*	The Engine class is the brain of the project. Every module alone is "almost useless"; 
*	the real power comes through combination with other modules, and that's the job of the 
*	Engine. Glue code for communication between engines, right order of startup, shutdown and 
*	execution. Manage the Application.
*	
*/


export module gargantua.core.engine;

import <concepts>;
import <string_view>;

import gargantua.types;
import gargantua.log;
import gargantua.app.application;
import gargantua.time;


namespace gargantua::core
{
	export
	class Engine
	{
	public:
		//Engine();
		Engine(const u32 width, const u32 height, std::string_view title);
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
		auto RegisterListenersToEvents() -> void;
		 
	private:
		bool should_close;

		time::TimeSystem time_system;
		unique_res<app::Application> application;
	};
} // namespace gargantua::core

