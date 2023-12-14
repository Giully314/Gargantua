/*
* gargantua/input/input_keyboardevents.ixx
* 
* PURPOSE: define keyboard events.
* 
* CLASSES:
*	KeyEvent: A key event. Stores the key code.
*	KeyPressedEvent: Information about the key pressed.
*	KeyReleasedEvent: Information about the key released.
*/

export module gargantua.input.keyboard_events;

import gargantua.types;
import gargantua.event.base_event;
import gargantua.input.key_codes;

export namespace gargantua::input
{
	struct KeyEvent : event::BaseEvent
	{
		constexpr explicit KeyEvent(const Key key_) : key(key_)
		{

		}

		const Key key;
	};

	struct KeyPressedEvent final : KeyEvent
	{
		constexpr explicit KeyPressedEvent(const Key key) : KeyEvent(key)
		{

		}
	};


	struct KeyReleasedEvent final : KeyEvent
	{
		constexpr explicit KeyReleasedEvent(const Key key) : KeyEvent(key)
		{

		}
	};
} // namespace gargantua::input