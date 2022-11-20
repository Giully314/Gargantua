/*
gargantua/event/window_events.ixx

PURPOSE: Window events.

CLASSES:
	WindowEvent: base event struct for window. Specify the static type of the event.
	WindowResizeEvent: New window sizes information.
	WindowCloseEvent: Window close signal.

DESCRIPTION:
	Basic events for handling window changes.

USAGE:


TODO: Window input focus, window focus, window refresh, 

*/

module;

#include "events_macro.hpp"

export module gargantua.event.window_events;

import gargantua.types;

import gargantua.event.base_event;


export namespace gargantua::event
{

	struct WindowEvent : public BaseEvent
	{
		WindowEvent() : BaseEvent(StaticEventType::WindowEvent) { }

		EVENT_NAME;
		GET_EVENT_NAME
	}; //struct WindowEvent


	struct WindowResizeEvent : public WindowEvent
	{
		WindowResizeEvent(natural_t new_width_, natural_t new_height_) :
			new_width(new_width_), new_height(new_height_)
		{

		}

		EVENT_NAME;
		GET_EVENT_NAME

		const natural_t new_width;
		const natural_t new_height;
	}; //struct WindowResizeEvent


	struct WindowCloseEvent : public WindowEvent
	{
		WindowCloseEvent(bool is_closed_) : is_closed(is_closed_)
		{

		}

		EVENT_NAME;
		GET_EVENT_NAME

		const bool is_closed;
	}; //struct WindowCloseEvent

} //namespace gargantua::event