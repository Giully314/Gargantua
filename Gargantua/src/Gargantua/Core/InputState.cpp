#include "InputState.hpp"

#include "Gargantua/Core/EngineLogger.hpp"
#include "Gargantua/Event/KeyEvents.hpp"
#include "Gargantua/Event/MouseEvents.hpp"

namespace Gargantua
{
	namespace Core
	{
		UniqueRes<Input::KeyboardState> InputState::keyboard{nullptr};
		UniqueRes<Input::MouseState> InputState::mouse{nullptr};

		InputState::InputState()
		{
			GRG_CORE_DEBUG("InputState Constructor");
			Init();
		}


		void InputState::Init()
		{
			GRG_CORE_DEBUG("InputState Init");
			keyboard = CreateUniqueRes<Input::KeyboardState>();
			mouse = CreateUniqueRes<Input::MouseState>();
		}


		void InputState::ListenToEvents(NonOwnedRes<Event::EventListenerSystem> event_list_sys)
		{
			event_list_sys->RegisterListener<Event::KeyPressedEvent>([=](const Event::BaseEvent& e)
				{
					const auto& ie = static_cast<const Event::KeyPressedEvent&>(e);
					keyboard->SetKey(ie.key_code, true);
				});

			event_list_sys->RegisterListener<Event::KeyReleasedEvent>([=](const Event::BaseEvent& e)
				{
					const auto& ie = static_cast<const Event::KeyReleasedEvent&>(e);
					keyboard->SetKey(ie.key_code, false);
				});

			event_list_sys->RegisterListener<Event::MouseCursorEvent>([=](const Event::BaseEvent& e)
				{
					const auto& ie = static_cast<const Event::MouseCursorEvent&>(e);
					mouse->SetCoords(ie.x, ie.y);
				});

			event_list_sys->RegisterListener<Event::MouseButtonPressedEvent>([=](const Event::BaseEvent& e)
				{
					const auto& ie = static_cast<const Event::MouseButtonPressedEvent&>(e);
					mouse->SetButton(ie.button, true);
				});

			event_list_sys->RegisterListener<Event::MouseButtonReleasedEvent>([=](const Event::BaseEvent& e)
				{
					const auto& ie = static_cast<const Event::MouseButtonReleasedEvent&>(e);
					mouse->SetButton(ie.button, false);
				});
		}
	} //namespace Input
} //namespace Gargantua