/*
* gargantua/core/engine.cpp
*/

#include <gargantua/log/logger_macro.hpp>

module gargantua.core.engine;

namespace gargantua::core
{
	Engine::Engine() : Engine(720, 480, "test")
	{

	}

	Engine::Engine(const u32 width, const u32 height, std::string_view title) : should_close(false)
	{
		GRG_CORE_DEBUG("Start engine");
		plat_event_dispatcher = CreateSharedRes<platform::PlatformEventDispatcher>();
		window = CreateSharedRes<platform::Window>(width, height, title, plat_event_dispatcher);
		window->RegisterEvents();
		input_peripheral = CreateSharedRes<platform::InputSystem>();
		input_peripheral->RegisterListenersToEvents(plat_event_dispatcher);

		RegisterListenersToEvents();

	}


	auto Engine::RegisterListenersToEvents() -> void
	{
		plat_event_dispatcher->RegisterListener<platform::WindowCloseEvent>([this](const platform::WindowCloseEvent& e)
			{
				should_close = e.is_closed;
			});
	}

	auto Engine::Run() -> void
	{
		GRG_CORE_DEBUG("Engine run with value {}", 10);
		while (!should_close && !input_peripheral->keyboard.IsPressed(platform::Key::ESCAPE))
		{
			window->Update();
		}
	}
}
