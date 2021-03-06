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


TODO:
	clean up the code (expecially in the constructor). Too much code in a single function, bad readability.

*/

#include "Gargantua/Types.hpp"


#include "Gargantua/Core/Application.hpp"
#include "Gargantua/Core/EngineLogger.hpp"
#include "Gargantua/Core/Window.hpp"
#include "Gargantua/Core/ImGuiStage.hpp"
#include "Gargantua/Core/EngineSystems.hpp"
#include "Gargantua/Core/Scene2d.hpp"

#include "Gargantua/Systems/EventSystem.hpp"
#include "Gargantua/Systems/InputSystem.hpp"
#include "Gargantua/Systems/Renderer2dSystem.hpp"
#include "Gargantua/Systems/ShaderSystem.hpp"
#include "Gargantua/Systems/ECSSystem.hpp"
#include "Gargantua/Systems/TimeSystem.hpp"


#include <functional>



namespace Gargantua
{
	class Engine
	{
	public:
		Engine(std::function<Core::Application*(void)> create_app);
		Engine(std::function<Core::Application*(void)> create_app, natural_t width, natural_t height);

		~Engine();


		SharedRes<Core::Window> GetWindow() const noexcept 
		{
			return window;
		}


		void Run();


	private:
		bool should_close;

		//Current application in execution.
		UniqueRes<Core::Application> app;	
		UniqueRes<Core::EngineLogger> engine_logger;
		SharedRes<Core::Window> window;
		

		//Use the EngineSystems struct?
		SharedRes<Systems::EventSystem> engine_event_sys;
		SharedRes<Systems::EventSystem> app_event_sys;
		SharedRes<Systems::InputSystem> input_sys;
		SharedRes<Systems::Renderer2dSystem> renderer2d_sys;
		SharedRes<Systems::ShaderSystem> shader_sys;
		SharedRes<Systems::ECSSystem> ecs_sys;
		SharedRes<Systems::TimeSystem> time_sys;

		//SharedRes<Core::Scene2d> scene2d;

		UniqueRes<Core::ImGuiStage> gui_stage;
	};
} //namespace Gargantua