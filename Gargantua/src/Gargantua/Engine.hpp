#pragma once 
/*
Gargantua/Engine.hpp

PURPOSE: Engine. Make the all systems to work together.

CLASSES: 
	Engine: The whole brain.


DESCRIPTION:
	This class is more than simple glue code for the systems and other components; 
	it's like the central nervous system. 
	Entry point of the engine.
	Controls the initialization of every system and component.
	Provide the game loop.
*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Time/Stopwatch.hpp"

#include "Gargantua/Core/Application.hpp"
#include "Gargantua/Core/EngineLogger.hpp"
#include "Gargantua/Core/Window.hpp"
#include "Gargantua/Core/ImGuiStage.hpp"
#include "Gargantua/Core/EngineSystems.hpp"

#include "Gargantua/Systems/EventSystem.hpp"
#include "Gargantua/Systems/InputSystem.hpp"
#include "Gargantua/Systems/RendererSystem.hpp"

#include <functional>



namespace Gargantua
{
	class Engine
	{
	public:
		Engine(std::function<Core::Application*(void)> create_app);
		~Engine();


		inline NonOwnedRes<Core::Window> GetWindow() const noexcept 
		{
			return window.get();
		}


		void Run();


	private:
		bool should_close;

		//Current application in execution.
		UniqueRes<Core::Application> app;	
		UniqueRes<Core::EngineLogger> engine_logger;
		UniqueRes<Core::Window> window;
		
		UniqueRes<Time::Stopwatch> stopwatch;

		SharedRes<Systems::EventSystem> engine_event_sys;
		SharedRes<Systems::EventSystem> app_event_sys;
		SharedRes<Systems::InputSystem> input_sys;
		SharedRes<Systems::RendererSystem> renderer_sys;

		UniqueRes<Core::ImGuiStage> gui_stage;
	};
} //namespace Gargantua