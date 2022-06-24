#pragma once
/*
Gargantua/Event/ImGuiEvents.hpp

PURPOSE: Dear ImGui events.

CLASSES:
	ImGuiEvent: base class for ImGui events.
	ImGuiPanelResizeEvent: info about panel resize events.


DESCRIPTION:


USAGE:
	
*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Event/BaseEvent.hpp"


namespace Gargantua
{
	namespace Event
	{
		struct ImGuiEvent : public BaseEvent
		{
			ImGuiEvent() : BaseEvent(StaticEventType::ImGuiEvent) { }

			EVENT_NAME;
			GET_EVENT_NAME
		};

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
		};
	} //namespace Event 
} //namespace Gargantua
