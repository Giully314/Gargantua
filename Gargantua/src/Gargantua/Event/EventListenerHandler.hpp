#pragma once
/*
Gargantua/Event/EventListenerHandler.hpp

PURPOSE: handler for the EventListenerSystem.

CLASSES:
	EventListenerHandler: interface for interacting with the low level event listener.

DESCRIPTION:
	This class acts like an iterator. Provide a unirofm interface to access the low level "container".

USAGE:
	EventListenerHandler elh{address_of_eventlistenersystem};

	elh.GetEventListeners("event_type_name");

*/


#include "Gargantua/Types.hpp"

#include "Gargantua/Concepts/Event.hpp"

#include "Gargantua/Event/EventListenerManager.hpp"

#include <ranges>
#include <string>


namespace Gargantua
{
	namespace Event
	{
		class EventListenerHandler
		{
		public:
			EventListenerHandler(NonOwnedRes<EventListenerManager>);


			auto GetEventListeners(const event_name_t& event_name)
			{
				return hdl->callbacks[event_name] | std::views::values;
			}

			auto GetEventListeners()
			{
				return hdl->callbacks | std::views::all;
			}


			inline NonOwnedRes<EventListenerManager> GetEventListenerSystem() { return hdl; }
			
			inline void SetEventListenerSystem(NonOwnedRes<EventListenerManager> els)
			{
				hdl = els;
			}

		private:
			NonOwnedRes<EventListenerManager> hdl;
		};
	} //namespace Event
} //namespace Gargantua



