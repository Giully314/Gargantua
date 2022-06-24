/*
Gargantua/Engine.cpp


OVERVIEW:
	The 2 core functions are the constructor and the Run method.
	The implementation is straightforward; look at the comments for more info.

*/

#include "Engine.hpp"

#include "Gargantua/Time/TimeStep.hpp"

#include "Gargantua/Event/BaseEvent.hpp"
#include "Gargantua/Event/WindowEvents.hpp"


namespace Gargantua
{
	Engine::Engine(std::function<Core::Application* (void)> create_app) : Engine(std::move(create_app), 1080, 720)
	{
		
	}

	Engine::Engine(std::function<Core::Application* (void)> create_app, natural_t width, natural_t height) : should_close(false)
	{
		engine_logger = CreateUniqueRes<Core::EngineLogger>();

		window = CreateSharedRes<Core::Window>("GargantuaEngine", width, height);
		
		/*
		The vsync should be used in combo with the time system to coordinate the 2 concepts.
		*/
		window->SetVSync(false);


		//Creation of the systems.
		engine_event_sys = CreateSharedRes<Systems::EventSystem>();
		app_event_sys = CreateSharedRes<Systems::EventSystem>();
		input_sys = CreateSharedRes<Systems::InputSystem>();
		renderer2d_sys = CreateSharedRes<Systems::Renderer2dSystem>(width, height);
		shader_sys = CreateSharedRes<Systems::ShaderSystem>();
		ecs_sys = CreateSharedRes<Systems::ECSSystem<ListOfComponents, ListOfSystems>>();
		time_sys = CreateSharedRes<Systems::TimeSystem>();



		//Register components to the engine event systems.
		window->ListenAndRegisterEvents(engine_event_sys);

		input_sys->ListenAndRegisterEvents(engine_event_sys);

		engine_event_sys->RegisterListener<Event::WindowCloseEvent>([this](const Event::BaseEvent& e)
			{
				const auto& we = static_cast<const Event::WindowCloseEvent&>(e);
				should_close = we.is_closed;
			});


		//Init after window has registered events.
		gui_stage = CreateUniqueRes<Core::ImGuiStage>(window);

		//Create the app using the function passed by the user.
		app = UniqueRes<Core::Application>(create_app());

		auto& systems = app->GetEngineSystems();
		systems.engine_event_sys = engine_event_sys;
		systems.app_event_sys = app_event_sys;
		systems.renderer2d_sys = renderer2d_sys;
		systems.shader_sys = shader_sys;
		systems.ecs_sys = ecs_sys;
		systems.time_sys = time_sys;
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
	-engine_event_sys deals with all events created in the previous frame (engine events).
	-app_event_sys deals with all events created in the previous frame (app events).
	-Clear the window.
	-Call Application::Execute(timestep).
	-Render frame.
	-UpdateWindow.

	-Shutdown the application.
	*/
	void Engine::Run()
	{
		GRG_CORE_INFO("Start of the Run method");
		app->Start();


		time_sys->SetUpdatePerSecond(60.0);

		while (!should_close)
		{

			time_sys->ComputeFrameTime();
			const Systems::TimeInfo& info = time_sys->GetInfo();
			
			//Update the logic with a fixed time step.
			do
			{
				time_sys->Tick();
				engine_event_sys->ProcessEvents();
				app_event_sys->ProcessEvents();
				app->Execute(info.ts);
			} while (info.valid);


			//Render the scene.

			gui_stage->Start();
			app->RenderGUI();
			gui_stage->End();

			window->Update();
			
		}	

		app->Shutdown();
	}
} //namespace Gargantua