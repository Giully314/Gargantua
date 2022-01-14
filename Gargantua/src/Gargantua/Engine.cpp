#include "Engine.hpp"

#include "Gargantua/Core/EngineLogger.hpp"
#include "Gargantua/Time/TimeStep.hpp"


#include "Gargantua/Event/BaseEvent.hpp"
#include "Gargantua/Event/WindowEvents.hpp"

namespace Gargantua
{
	Engine::Engine(std::function<Core::Application* (void)> create_app) : should_close(false)
	{
		Core::EngineLogger::Start();

		stopwatch = CreateUniqueRes<Time::Stopwatch>();

		app = UniqueRes<Core::Application>(create_app());
	}


	Engine::~Engine()
	{
		//Shutdown engine systems.
	}

	/*
	This is the application loop (or game loop). Here is executed the following pipeline: 
	TODO: https://stackoverflow.com/questions/59441699/gaffer-on-games-timestep-stdchrono-implementation

	-Start the application.
	-Calculate current TimeStep and update the internal Stopwatch.
	-EngineEventHandler deals with all events created in the previous frame (engine events).
	-ApplicationEventHandler deals with all events created in the previous frame (game events).
	-Call Application::Execute(timestep).
	-UpdateWindow.

	-Shutdown the application.
	*/
	void Engine::Run()
	{
		GRG_CORE_DEBUG("Start of the Run method");
		app->Start();
		stopwatch->Tick();

		while (should_close)
		{
			Time::TimeStep ts = stopwatch->Tick();

			app->Execute(ts);
		}	

		app->Shutdown();
	}
} //namespace Gargantua