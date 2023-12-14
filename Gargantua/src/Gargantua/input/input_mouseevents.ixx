/*
* gargantua/input/input_mouseevents.ixx
* 
* PURPOSE: define mouse events.
* 
* CLASSES:
*	MouseCursorEvent: Stores the new position of the cursor.	
*	MouseButtonEvent: Stores the mouse button code.
*	MouseButtonPressedEvent: Information about the mouse button pressed.
*	MouseButtonReleasedEvent: Information about the mouse button released.
*	MouseWheelScrollEvent: Stores the offset of the wheel.
*/

export module gargantua.input.mouse_events;


import gargantua.types;
import gargantua.input.mouse_codes;
import gargantua.event.base_event;


export namespace gargantua::input
{
	struct MouseCursorEvent : event::BaseEvent
	{
		constexpr explicit MouseCursorEvent(const f32 x_, const f32 y_) : x(x_), y(y_)
		{

		}


		const f32 x;
		const f32 y;
	};


	struct MouseButtonEvent : event::BaseEvent
	{
		constexpr explicit MouseButtonEvent(const MouseButton button_) : button(button_)
		{
		}

		const MouseButton button;
	};


	struct MouseButtonPressedEvent final : MouseButtonEvent
	{
		constexpr explicit MouseButtonPressedEvent(const MouseButton button_) : MouseButtonEvent(button_)
		{

		}
	};

	struct MouseButtonReleasedEvent final : MouseButtonEvent
	{
		constexpr explicit MouseButtonReleasedEvent(const MouseButton button_) : MouseButtonEvent(button_)
		{

		}
	};


	struct MouseWheelScrollEvent final : event::BaseEvent
	{
		constexpr explicit MouseWheelScrollEvent(const f32 y_offset_) : y_offset(y_offset_)
		{

		}

		const f32 y_offset;
	};
} // namespace gargantua::input