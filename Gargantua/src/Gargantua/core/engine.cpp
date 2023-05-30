/*
* gargantua/core/engine.cpp
*/

module;

#include <glad/glad.h>

#include <gargantua/log/logger_macro.hpp>

module gargantua.core.engine;

import gargantua.render.renderer2d_system;
import gargantua.platform.platform;
import gargantua.ecs.ecs;

namespace gargantua::core
{
	/*Engine::Engine() : Engine(720, 480, "test")
	{

	}*/

	Engine::Engine(const u32 width, const u32 height, std::string_view title) : should_close(false)
	{
		GRG_CORE_DEBUG("Start engine");
		
		// Platform system must be the first one to be initialized.
		platform::PlatformSystem::Instance().Startup(width, height, title);
		ecs::ECSSystem::Instance();
		render::Renderer2dSystem::Instance().Startup();

		time_system.Startup();


		// Register to the events after the initialization of platform system.
		RegisterListenersToEvents();
	}

	Engine::~Engine()
	{
		// Order does matter.
		application->Shutdown();
		render::Renderer2dSystem::Instance().Shutdown();
		platform::PlatformSystem::Instance().Shutdown();
	}

	auto Engine::RegisterListenersToEvents() -> void
	{
		platform::PlatformEventDispatcher::Instance()
			.RegisterListener<platform::WindowCloseEvent>([this](const platform::WindowCloseEvent& e)
			{
				should_close = e.is_closed;
			});
	}

	auto Engine::Run() -> void
	{
		application->Startup();
		app::ApplicationState state = app::ApplicationState::Running;
		auto& input_sys = platform::InputSystem::Instance();
		auto& plat_sys = platform::PlatformSystem::Instance();
		while (!should_close && !input_sys.IsPressed(platform::Key::ESCAPE) && 
			state == app::ApplicationState::Running)
		{
			auto ts = time_system.Tick();
			plat_sys.Run();

			// Update application.
			application->Begin();
			state = application->Run(ts);
			application->End();

			
			// Render ImGui.
			plat_sys.RenderGUI(application.get());
		}
	}
}

