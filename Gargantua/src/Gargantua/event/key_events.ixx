/*
gargantua/event/key_events.ixx

PURPOSE: Keyboard events.

CLASSES:
	KeyEvent: Information about the key code.
	KeyPressedEvent: Information about the key pressed.
	KeyReleasedEvent: Information about the key released.

DESCRIPTION:
	Basic events for handling keaboard changes.

USAGE:
*/
module;

#include "events_macro.hpp"

export module gargantua.event.key_events;

import gargantua.types;

import gargantua.event.base_event;


export namespace gargantua::event
{

	struct KeyEvent : public BaseEvent
	{
		KeyEvent(key_t key_code_) : BaseEvent(StaticEventType::KeyboardEvent), key_code(key_code_)
		{

		}


		EVENT_NAME;
		GET_EVENT_NAME

		const key_t key_code;
	}; //struct KeyEvent


	struct KeyPressedEvent : public KeyEvent
	{
		KeyPressedEvent(key_t key_code_) : KeyEvent(key_code_)
		{

		}

		EVENT_NAME;
		GET_EVENT_NAME
	}; //struct KeyPressedEvent


	struct KeyReleasedEvent : public KeyEvent
	{
		KeyReleasedEvent(key_t key_code_) : KeyEvent(key_code_)
		{

		}

		EVENT_NAME;
		GET_EVENT_NAME
	}; //struct KeyReleasedEvent

} //namespace gargantua::event

