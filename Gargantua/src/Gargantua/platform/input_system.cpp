/*
* gargantua/platform/input_system.cpp
*/

module gargantua.platform.input_system;

namespace gargantua::platform
{
	auto InputSystem::Startup() -> void
	{
		auto& event_dispatcher = PlatformEventDispatcher::Instance();
		event_dispatcher.RegisterListener<KeyPressedEvent>([=](const BaseEvent& e)
			{
				const auto& ie = static_cast<const KeyPressedEvent&>(e);
				keyboard.SetKey(ie.key, true);
			});

		event_dispatcher.RegisterListener<KeyReleasedEvent>([=](const BaseEvent& e)
			{
				const auto& ie = static_cast<const KeyReleasedEvent&>(e);
				keyboard.SetKey(ie.key, false);
			});

		event_dispatcher.RegisterListener<MouseCursorEvent>([=](const BaseEvent& e)
			{
				const auto& ie = static_cast<const MouseCursorEvent&>(e);
				mouse.SetPosition(ie.x, ie.y);
			});

		event_dispatcher.RegisterListener<MouseButtonPressedEvent>([=](const BaseEvent& e)
			{
				const auto& ie = static_cast<const MouseButtonPressedEvent&>(e);
				mouse.SetButton(ie.button, true);
			});

		event_dispatcher.RegisterListener<MouseButtonReleasedEvent>([=](const BaseEvent& e)
			{
				const auto& ie = static_cast<const MouseButtonReleasedEvent&>(e);
				mouse.SetButton(ie.button, false);
			});
	}
} // namespace gargantua::platform
