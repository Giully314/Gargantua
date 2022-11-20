/*
gargantua/event/mouseEvents.ixx

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

module;

#include "events_macro.hpp"

export module gargantua.event.mouse_events;

import gargantua.types;

import gargantua.event.base_event;


export namespace gargantua::event
{
	
		struct MouseEvent : public BaseEvent
		{
			MouseEvent() : BaseEvent(StaticEventType::MouseEvent) { }

			EVENT_NAME;
			GET_EVENT_NAME
		}; //struct MouseEvent


		struct MouseCursorEvent : public MouseEvent
		{
			MouseCursorEvent(real_t x_, real_t y_) : x(x_), y(y_)
			{

			}

			EVENT_NAME;
			GET_EVENT_NAME


				real_t x;
			real_t y;
		}; //struct MouseCursorEvent


		struct MouseButtonEvent : public MouseEvent
		{
			MouseButtonEvent(mouse_t button_) : button(button_)
			{
			}

			EVENT_NAME;
			GET_EVENT_NAME

				const mouse_t button;
		}; //struct MouseButtonEvent


		struct MouseButtonPressedEvent : public MouseButtonEvent
		{
			MouseButtonPressedEvent(mouse_t button_) : MouseButtonEvent(button_)
			{

			}

			EVENT_NAME;
			GET_EVENT_NAME
		}; //struct MouseButtonPressedEvent


		struct MouseButtonReleasedEvent : public MouseButtonEvent
		{
			MouseButtonReleasedEvent(mouse_t button_) : MouseButtonEvent(button_)
			{

			}

			EVENT_NAME;
			GET_EVENT_NAME
		}; //struct MouseButtonReleasedEvent



		struct MouseWheelScrollEvent : public MouseEvent
		{
			MouseWheelScrollEvent(real_t y_offset_) : y_offset(y_offset_)
			{

			}

			EVENT_NAME;
			GET_EVENT_NAME


				real_t y_offset;
		}; //struct MouseWheelScrollEvent

} //namespace gargantua::event

