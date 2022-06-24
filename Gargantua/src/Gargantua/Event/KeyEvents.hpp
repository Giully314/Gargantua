#pragma once
/*
Gargantua/Event/KeyEvents.hpp

PURPOSE: Keyboard events.

CLASSES:
	KeyEvent: Information about the key code.
	KeyPressedEvent: Information about the key pressed.
	KeyReleasedEvent: Information about the key released.

DESCRIPTION:
	Basic events for handling keaboard changes.

USAGE:
*/

#include "Gargantua/Event/BaseEvent.hpp"
#include "Gargantua/Types.hpp"

namespace Gargantua
{
	namespace Event
	{
		struct KeyEvent : public BaseEvent
		{
			KeyEvent(key_t key_code_) : BaseEvent(StaticEventType::KeyboardEvent), key_code(key_code_)
			{

			}


			EVENT_NAME;
			GET_EVENT_NAME

			const key_t key_code;
		};


		struct KeyPressedEvent : public KeyEvent
		{
			KeyPressedEvent(key_t key_code_) : KeyEvent(key_code_)
			{

			}

			EVENT_NAME;
			GET_EVENT_NAME
		};


		struct KeyReleasedEvent : public KeyEvent
		{
			KeyReleasedEvent(key_t key_code_) : KeyEvent(key_code_)
			{

			}

			EVENT_NAME;
			GET_EVENT_NAME
		};
	} //namespace Event
} //namespace Gargantua

