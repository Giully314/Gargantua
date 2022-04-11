/*
Gargantua/Systems/InputSystem.cpp
*/
#include "InputSystem.hpp"

#include "Gargantua/Core/EngineLogger.hpp"
#include "Gargantua/Event/KeyEvents.hpp"
#include "Gargantua/Event/MouseEvents.hpp"

namespace Gargantua
{
	namespace Systems
	{
		UniqueRes<Input::KeyboardState> InputSystem::keyboard{nullptr};
		UniqueRes<Input::MouseState> InputSystem::mouse{nullptr};

		InputSystem::InputSystem()
		{
			GRG_CORE_DEBUG("InputSystem Init");
			keyboard = CreateUniqueRes<Input::KeyboardState>();
			mouse = CreateUniqueRes<Input::MouseState>();
		}


		void InputSystem::ListenToEvents(NonOwnedRes<Event::EventListenerManager> event_list_mng)
		{
			event_list_mng->RegisterListener<Event::KeyPressedEvent>([=](const Event::BaseEvent& e)
				{
					const auto& ie = static_cast<const Event::KeyPressedEvent&>(e);
					keyboard->SetKey(ie.key_code, true);
				});

			event_list_mng->RegisterListener<Event::KeyReleasedEvent>([=](const Event::BaseEvent& e)
				{
					const auto& ie = static_cast<const Event::KeyReleasedEvent&>(e);
					keyboard->SetKey(ie.key_code, false);
				});

			event_list_mng->RegisterListener<Event::MouseCursorEvent>([=](const Event::BaseEvent& e)
				{
					const auto& ie = static_cast<const Event::MouseCursorEvent&>(e);
					mouse->SetCoords(ie.x, ie.y);
				});

			event_list_mng->RegisterListener<Event::MouseButtonPressedEvent>([=](const Event::BaseEvent& e)
				{
					const auto& ie = static_cast<const Event::MouseButtonPressedEvent&>(e);
					mouse->SetButton(ie.button, true);
				});

			event_list_mng->RegisterListener<Event::MouseButtonReleasedEvent>([=](const Event::BaseEvent& e)
				{
					const auto& ie = static_cast<const Event::MouseButtonReleasedEvent&>(e);
					mouse->SetButton(ie.button, false);
				});
		}
	} //namespace Systems
} //namespace Gargantua