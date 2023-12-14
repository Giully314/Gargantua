/*
* gargantua/core/core_engine.cpp
*/

module;

#include <glad/glad.h>

#include <gargantua/log/logger_macro.hpp>

module gargantua.core.engine;

import gargantua.event.base_event;
import gargantua.event.engine_event_dispatcher;
import gargantua.input;
import gargantua.parallel;
import gargantua.render;
import gargantua.imgui;

namespace gargantua::core
{
	Engine::Engine(const u32 width, const u32 height, const std::string_view title) : should_close(false)
	{
		GRG_CORE_DEBUG("Start engine");
		
		// Order of initialization matters because some systems depend on others.
		auto& engine_event_dispatcher = event::EngineEventDispatcher(); 
		glfw_system.Startup();
		window = CreateUniqueRes<glfw::Window>(width, height, title);
		input::InputSystem::Instance().Startup();
		parallel::TaskSystem::Instance().Startup();
		imgui::ImGuiSystem::Instance().Startup(window.get());
		// TODO: initialize shader and texture systems?
		render::RendererSystem::Instance().Startup(width, height);


		// Register to the events after the initialization of platform system.
		engine_event_dispatcher.RegisterListener<glfw::WindowCloseEvent>([this](const event::BaseEvent& e)
			{
				const auto& ew = static_cast<const glfw::WindowCloseEvent&>(e);
				should_close = ew.is_closed;
			});
	}

	Engine::~Engine()
	{
		// Order does matter.

		render::RendererSystem::Instance().Shutdown();
		imgui::ImGuiSystem::Instance().Shutdown();
		parallel::TaskSystem::Instance().Shutdown();
		input::InputSystem::Instance().Shutdown();
		window.reset();
		glfw_system.Shutdown();

		GRG_CORE_DEBUG("Shutdown engine.");
	}


	auto Engine::Run() -> void
	{
		auto& input_sys = input::InputSystem::Instance();
		auto& imgui_sys = imgui::ImGuiSystem::Instance();

		application->Startup();
		auto application_state = app::ApplicationState::Running;

		// TODO: make the frame/update rate stable and allow the option to set it from user code.

		// start the stopwatch
		stopwatch.Tick();
		while (!should_close && !input_sys.IsPressed(input::Key::Escape) && 
			application_state == app::ApplicationState::Running)
		{
			auto ts = stopwatch.Tick();
			input_sys.Run();
			window->Update();

			application->Begin();
			application_state = application->Run(ts);
			application->End();

			// TODO: this should not be here because the usage of imgui is optional.
			// This imgui begin and scene scene should be in the user code.
			imgui_sys.BeginScene();
			application->RenderGUI();
			imgui_sys.EndScene();
		}

		application->Shutdown();
	}
}

