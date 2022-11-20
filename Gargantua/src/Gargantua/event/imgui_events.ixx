/*
gargantua/event/imgui_events.ixx

PURPOSE: Dear ImGui events.

CLASSES:
	ImGuiEvent: base class for ImGui events.
	ImGuiPanelResizeEvent: info about panel resize events.


DESCRIPTION:


USAGE:

*/

module;

#include "events_macro.hpp"

export module gargantua.event.imgui_events;

import gargantua.types;

import gargantua.event.base_event;


namespace gargantua::event
{

	struct ImGuiEvent : public BaseEvent
	{
		ImGuiEvent() : BaseEvent(StaticEventType::ImGuiEvent) { }

		EVENT_NAME;
		GET_EVENT_NAME
	}; //struct ImGuiEvent

	struct ImGuiPanelResizeEvent : public BaseEvent
	{
		ImGuiPanelResizeEvent(natural_t new_width_, natural_t new_height_) :
			new_width(new_width_), new_height(new_height_)
		{

		}

		EVENT_NAME;
		GET_EVENT_NAME

		const natural_t new_width;
		const natural_t new_height;
	}; //struct ImGuiPanelResizeEvent

} //namespace gargantua::event
