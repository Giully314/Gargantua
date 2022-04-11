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

		stopwatch = CreateUniqueRes<Time::Stopwatch>();

		//Creation of the systems.
		engine_event_sys = CreateSharedRes<Systems::EventSystem>();
		app_event_sys = CreateSharedRes<Systems::EventSystem>();
		input_sys = CreateSharedRes<Systems::InputSystem>();
		renderer_sys = CreateSharedRes<Systems::RendererSystem>(width, height);
		renderer2d_sys = CreateSharedRes<Systems::Renderer2dSystem>(width, height);
		shader_sys = CreateSharedRes<Systems::ShaderSystem>();


		//Register components to the engine event systems.
		auto event_list_mng = engine_event_sys->GetEventListenerManager();
		auto event_reg_mng = engine_event_sys->GetEventRegisterManager();

		window->ListenToEvents(event_list_mng);
		window->RegisterEvents(event_reg_mng);

		input_sys->ListenToEvents(event_list_mng);

		renderer_sys->ListenToEvents(event_list_mng);

		event_list_mng->RegisterListener<Event::WindowCloseEvent>([this](const Event::BaseEvent& e)
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
		systems.renderer_sys = renderer_sys;
		systems.renderer2d_sys = renderer2d_sys;
		systems.shader_sys = shader_sys;
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
		stopwatch->Tick();

		real64_t t = 0.0;
		const real64_t frame_per_sec = 20;
		const real64_t single_frame = 1.0 / frame_per_sec;

		while (!should_close)
		{
			Time::TimeStep ts = stopwatch->Tick();
			//GRG_CORE_DEBUG("Time elapsed: {}", ts.GetInMilliSec());
			t += ts.GetInMilliSec();

			if (t >= single_frame)
			{
				t -= single_frame;
				
				engine_event_sys->ProcessEvents();
				app_event_sys->ProcessEvents();


				app->Execute(ts);

				//Lazy renderer and physics
				//physics_sys.UpdateState();
				//renderer_sys->RenderFrame();


				gui_stage->Start();
				app->RenderGUI();
				gui_stage->End();

				window->Update();
			}
		}	

		app->Shutdown();
	}
} //namespace Gargantua