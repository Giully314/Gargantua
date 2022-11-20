/*
gargantua/system/input_system.cpp
*/

module gargantua.system.input_system;

import gargantua.event.events;

namespace gargantua::system
{

	UniqueRes<input::KeyboardState> InputSystem::keyboard{ nullptr };
	UniqueRes<input::MouseState> InputSystem::mouse{ nullptr };

	InputSystem::InputSystem()
	{
		//GRG_CORE_DEBUG("InputSystem Init");
		keyboard = CreateUniqueRes<input::KeyboardState>();
		mouse = CreateUniqueRes<input::MouseState>();
	}


	auto InputSystem::ListenAndRegisterEvents(SharedRes<system::EventSystem> event_sys) -> void
	{
		event_sys->RegisterListener<event::KeyPressedEvent>([=](const event::BaseEvent& e)
			{
				const auto& ie = static_cast<const event::KeyPressedEvent&>(e);
				keyboard->SetKey(ie.key_code, true);
			});

		event_sys->RegisterListener<event::KeyReleasedEvent>([=](const event::BaseEvent& e)
			{
				const auto& ie = static_cast<const event::KeyReleasedEvent&>(e);
				keyboard->SetKey(ie.key_code, false);
			});

		event_sys->RegisterListener<event::MouseCursorEvent>([=](const event::BaseEvent& e)
			{
				const auto& ie = static_cast<const event::MouseCursorEvent&>(e);
				mouse->SetCoords(ie.x, ie.y);
			});

		event_sys->RegisterListener<event::MouseButtonPressedEvent>([=](const event::BaseEvent& e)
			{
				const auto& ie = static_cast<const event::MouseButtonPressedEvent&>(e);
				mouse->SetButton(ie.button, true);
			});

		event_sys->RegisterListener<event::MouseButtonReleasedEvent>([=](const event::BaseEvent& e)
			{
				const auto& ie = static_cast<const event::MouseButtonReleasedEvent&>(e);
				mouse->SetButton(ie.button, false);
			});
	}

} //namespace gargantua::system