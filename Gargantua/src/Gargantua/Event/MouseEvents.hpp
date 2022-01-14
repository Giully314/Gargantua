#pragma once

#include "Gargantua/Event/BaseEvent.hpp"
#include "Gargantua/Types.hpp"


//TODO: mouse wheel events

namespace Gargantua
{
	namespace Event
	{
		struct MouseCursorEvent : public BaseEvent
		{
			MouseCursorEvent(real_t x_, real_t y_) : x(x_), y(y_)
			{

			}

			EVENT_NAME;
			GET_EVENT_NAME


			real_t x;
			real_t y;
		};


		struct MouseButtonEvent : public BaseEvent
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
	} //namespace Event
} //namespace Gargantua

