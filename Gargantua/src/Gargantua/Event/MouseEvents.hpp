#pragma once
/*
Gargantua/Event/MouseEvents.hpp

PURPOSE: Mouse events.

CLASSES:
	MouseCursorEvent: Information about the cursos position.
	MouseButtonEvent: Information about the button.
	MouseButtonPressedEvent: Information about the button pressed.
	MouseButtonReleasedEvent: Information about the button released.

DESCRIPTION:
	Basic events for handling mouse changes.

USAGE:
*/

#include "Gargantua/Event/BaseEvent.hpp"
#include "Gargantua/Types.hpp"


//TODO: mouse wheel events

namespace Gargantua
{
	namespace Event
	{
		struct MouseEvent : public BaseEvent
		{
			MouseEvent() : BaseEvent(StaticEventType::MouseEvent) { }

			EVENT_NAME;
			GET_EVENT_NAME
		};


		struct MouseCursorEvent : public MouseEvent
		{
			MouseCursorEvent(real_t x_, real_t y_) : x(x_), y(y_)
			{

			}

			EVENT_NAME;
			GET_EVENT_NAME


			real_t x;
			real_t y;
		};


		struct MouseButtonEvent : public MouseEvent
		{
			MouseButtonEvent(mouse_t button_) : button(button_)
			{
			}

			EVENT_NAME;
			GET_EVENT_NAME

			const mouse_t button;
		};


		struct MouseButtonPressedEvent : public MouseButtonEvent
		{
			MouseButtonPressedEvent(mouse_t button_) : MouseButtonEvent(button_)
			{

			}

			EVENT_NAME;
			GET_EVENT_NAME
		};


		struct MouseButtonReleasedEvent : public MouseButtonEvent
		{
			MouseButtonReleasedEvent(mouse_t button_) : MouseButtonEvent(button_)
			{

			}

			EVENT_NAME;
			GET_EVENT_NAME
		};



		struct MouseWheelScrollEvent : public MouseEvent
		{
			MouseWheelScrollEvent(real_t y_offset_) : y_offset(y_offset_)
			{

			}

			EVENT_NAME;
			GET_EVENT_NAME


			real_t y_offset;
		};

	} //namespace Event
} //namespace Gargantua

