#pragma once

#include "Gargantua/Types.hpp"


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
		An event SHOULD NOT HAVE objects that are dynamic created by itself. It's ok to have NonOwnedRes.
		So all the data should be heap free.
		This is essential because the events are created with a custom memory pool that is resetted 
		at the end of every frame without calling destructors (for fast performance).
		*/
		struct BaseEvent
		{
			//Note: the event type should be static const. Good to use strings with length less than 15.
			static const event_name_t EventName;

			BaseEvent() = default;

			BaseEvent(BaseEvent&&) noexcept = default;
			BaseEvent& operator=(BaseEvent&&) noexcept = default;

			virtual ~BaseEvent();

			virtual const event_name_t& GetEventName() const noexcept { return EventName; }
		};

#define EVENT_NAME static const event_name_t EventName
#define GET_EVENT_NAME virtual const event_name_t& GetEventName() const noexcept override { return EventName; }

	} //namespace Event
} //namespace Gargantua
