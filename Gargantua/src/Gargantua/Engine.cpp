#include "Engine.hpp"

#include "Gargantua/Time/TimeStep.hpp"

#include "Gargantua/Event/BaseEvent.hpp"
#include "Gargantua/Event/WindowEvents.hpp"

namespace Gargantua
{
	Engine::Engine(std::function<Core::Application* (void)> create_app) : should_close(false)
	{
		engine_logger = CreateUniqueRes<Core::EngineLogger>();
		event_system = CreateUniqueRes<Core::EventSystem>();
		window = CreateUniqueRes<Core::Window>("GargantuaEngine", 1080, 720);
		input_state = CreateUniqueRes<Core::InputState>();
		stopwatch = CreateUniqueRes<Time::Stopwatch>();

		auto event_list_sys = event_system->GetEventListenerSystem();
		auto event_reg_sys = event_system->GetEventRegisterSystem();

		window->ListenToEvents(event_list_sys);
		window->RegisterEvents(event_reg_sys);

		input_state->ListenToEvents(event_list_sys);

		//Listen to WindowCloseEvent to shutdown the application
		event_list_sys->RegisterListener<Event::WindowCloseEvent>([this](const Event::BaseEvent& e)
			{
				const auto& we = static_cast<const Event::WindowCloseEvent&>(e);
				should_close = we.is_closed;
			});


//#ifdef GRG_MODE_DEBUG
		//Only for debug purpose
		event_list_sys->RegisterListener<Event::KeyPressedEvent>([this](const Event::BaseEvent& e)
			{
				const auto& k = static_cast<const Event::KeyPressedEvent&>(e);
				GRG_CORE_DEBUG("Key pressed: {}", k.key_code);
			});

		event_list_sys->RegisterListener<Event::KeyReleasedEvent>([this](const Event::BaseEvent& e)
			{
				const auto& k = static_cast<const Event::KeyReleasedEvent&>(e);
				GRG_CORE_DEBUG("Key released: {}", k.key_code);
			});
//#endif


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

		real64_t t = 0.0;
		const real64_t frame_per_sec = 20;
		const real64_t single_frame = 1.0 / frame_per_sec;

		while (!should_close)
		{
			Time::TimeStep ts = stopwatch->Tick();
			GRG_CORE_DEBUG("Time elapsed: {}", ts.GetInMilliSec());
			t += ts.GetInMilliSec();

			if (t >= single_frame)
			{
				t -= single_frame;
				event_system->ProcessEvents();

				app->Execute(ts);

				window->Update();
			}
		}	

		app->Shutdown();
	}
} //namespace Gargantua