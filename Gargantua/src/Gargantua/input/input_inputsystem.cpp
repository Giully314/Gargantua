/*
* gargantua/input/input_inputsystem.cpp
*/

module;

#include <gargantua/log/logger_macro.hpp>

module gargantua.input.input_system;

import gargantua.event.engine_event_dispatcher;
import gargantua.input.keyboard_events;
import gargantua.input.mouse_events;
import gargantua.log;

namespace gargantua::input
{
	auto InputSystem::Startup() -> void
	{
		GRG_CORE_DEBUG("InputSystem startup.");

		auto& event_dispatcher = event::EngineEventDispatcher();
		event_dispatcher.RegisterListener<KeyPressedEvent>([this](const event::BaseEvent& e)
			{
				const auto& ie = static_cast<const KeyPressedEvent&>(e);
				keyboard.SetKey(ie.key, true);
			});

		event_dispatcher.RegisterListener<KeyReleasedEvent>([this](const event::BaseEvent& e)
			{
				const auto& ie = static_cast<const KeyReleasedEvent&>(e);
				keyboard.SetKey(ie.key, false);
			});

		event_dispatcher.RegisterListener<MouseCursorEvent>([this](const event::BaseEvent& e)
			{
				const auto& ie = static_cast<const MouseCursorEvent&>(e);
				mouse.SetPosition(ie.x, ie.y);
			});

		event_dispatcher.RegisterListener<MouseButtonPressedEvent>([this](const event::BaseEvent& e)
			{
				const auto& ie = static_cast<const MouseButtonPressedEvent&>(e);
				mouse.SetButton(ie.button, true);
			});

		event_dispatcher.RegisterListener<MouseButtonReleasedEvent>([this](const event::BaseEvent& e)
			{
				const auto& ie = static_cast<const MouseButtonReleasedEvent&>(e);
				mouse.SetButton(ie.button, false);
			});
	}
} // namespace gargantua::input
