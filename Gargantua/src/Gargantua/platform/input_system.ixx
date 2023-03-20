/*
* gargantua/platform/input_system.ixx
* 
* PURPOSE:
* CLASSES:
* DESCRIPTION:
* 
*/

export module gargantua.platform.input_system;

import gargantua.types;
import gargantua.platform.event_dispatcher;
import gargantua.platform.keyboard;
import gargantua.platform.mouse;
import gargantua.platform.platform_events;


export namespace gargantua::platform
{
	struct InputSystem
	{
		// Register listeners for all keyboard/mouse events.
		auto RegisterListenersToEvents(shared_res<PlatformEventDispatcher>& event_dispatcher) -> void
		{
			event_dispatcher->RegisterListener<KeyPressedEvent>([=](const BaseEvent& e)
				{
					const auto& ie = static_cast<const KeyPressedEvent&>(e);
					keyboard.SetKey(ie.key, true);
				});

			event_dispatcher->RegisterListener<KeyReleasedEvent>([=](const BaseEvent& e)
				{
					const auto& ie = static_cast<const KeyReleasedEvent&>(e);
					keyboard.SetKey(ie.key, false);
				});

			event_dispatcher->RegisterListener<MouseCursorEvent>([=](const BaseEvent& e)
				{
					const auto& ie = static_cast<const MouseCursorEvent&>(e);
					mouse.SetPosition(ie.x, ie.y);
				});

			event_dispatcher->RegisterListener<MouseButtonPressedEvent>([=](const BaseEvent& e)
				{
					const auto& ie = static_cast<const MouseButtonPressedEvent&>(e);
					mouse.SetButton(ie.button, true);
				});

			event_dispatcher->RegisterListener<MouseButtonReleasedEvent>([=](const BaseEvent& e)
				{
					const auto& ie = static_cast<const MouseButtonReleasedEvent&>(e);
					mouse.SetButton(ie.button, false);
				});
		}

		Keyboard keyboard;
		Mouse mouse;
	};
} // namespace gargantua::platform