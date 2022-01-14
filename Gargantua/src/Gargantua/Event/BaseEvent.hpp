#pragma once

#include <string>

namespace Gargantua
{
	namespace Event
	{
		/*
		Note for the future: a template version of the event system could be a thing to try,
		if performance are bad.
		*/


		/*
		For me, an event is something that happens, a change in state in a part of the application.
		An event is just a container for the informations that should be transported from a system to another,
		like a message (but not the same thing).
		*/
		struct BaseEvent
		{
			//Note: the event type should be static const. Good to use strings with length less than 15.
			using event_name_t = std::string;

			static const event_name_t EventName;

			virtual ~BaseEvent() = default;

			virtual const std::string& GetEventName() const noexcept { return EventName; }
		};
//
#define EVENT_NAME static const BaseEvent::event_name_t EventName
#define GET_EVENT_NAME virtual const std::string& GetEventName() const noexcept override { return EventName; }

	} //namespace Event
} //namespace Gargantua
