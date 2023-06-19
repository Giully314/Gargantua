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

import <concepts>;
import <string_view>;

import gargantua.types;
import gargantua.log.log;
import gargantua.app.application;
import gargantua.time.time;


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

