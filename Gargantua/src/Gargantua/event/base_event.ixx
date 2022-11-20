/*
gargantua/event/base_event.ixx

PURPOSE: abstract class for an event.

CLASSES:
	StaticEventType: enum for the static category of an event.
	BaseEvent: base abstract class for every event defined.

DESCRIPTION:
	For me, an event is something that happens, a change in state in a part of the program.
	An event is just a container for the informations that should be transported from a part to another,
	like a message (but not the same thing).
	An event SHOULD NOT HAVE objects that are dynamic created by itself. It's ok to have NonOwnedRes.
	So all the data should be heap free.

	(TODO)This is essential because the events are created with a custom memory pool that is resetted
	at the end of every frame without calling destructors (for fast performance).

USAGE:
	struct MyEvent : public Gargantua::Event::BaseEvent
	{
		static const event_name_t EventName;

		int attribute1;
	};


TODO:
	a template version of the event system could be a thing to try, if performance are bad.
*/

export module gargantua.event.base_event;

import <string>;

import gargantua.types;



export namespace gargantua::event
{
		/*
		This static type is used to dispatch event in the ProcessEvent function inside the EventSystem.
		The engine can block the process of one or more type of events.
		*/
		enum class StaticEventType : byte_t
		{
			UnknownEvent = 0,
			WindowEvent,
			KeyboardEvent,
			MouseEvent,
			ImGuiEvent,
		}; //enum class StaticEventType


		struct BaseEvent
		{
			//Note: the event type should be static const string.
			static const event_name_t EventName;

			BaseEvent() = default;

			BaseEvent(StaticEventType type) : static_type(type) { }

			BaseEvent(BaseEvent&&) noexcept = default;
			BaseEvent& operator=(BaseEvent&&) noexcept = default;

			virtual ~BaseEvent() = default;

			virtual auto GetEventName() const noexcept -> const event_name_t&
			{ 
				return EventName;	
			}


			StaticEventType static_type = StaticEventType::UnknownEvent;
		}; //struct BaseEvent

} //namespace gargantua::event
