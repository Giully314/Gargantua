#include "Engine.hpp"

#include "Gargantua/Time/TimeStep.hpp"

namespace Gargantua
{
	Engine::Engine(std::function<Core::Application* (void)> create_app) : app(nullptr)
	{
		

		app = UniqueRes<Core::Application>(create_app());
	}


	Engine::~Engine()
	{
		//Shutdown engine systems.
	}

	/*
	This is the application loop (or game loop). Here is executed the following pipeline: 
	-Calculate current TimeStep and update the internal Stopwatch.
	-EngineEventHandler deals with all events created in the previous frame (engine events).
	-ApplicationEventHandler deals with all events created in the previous frame (game events).
	-Call Application::Execute(timestep).
	-UpdateWindow.
	*/
	void Engine::Run()
	{
		stopwatch.Tick();

		while (true)
		{
			Time::TimeStep ts = stopwatch.Tick();


			app->Execute();
		}	
	}
} //namespace Gargantua