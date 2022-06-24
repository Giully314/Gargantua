#pragma once
/*
Gargantua/Event/EventRegisterHandler.hpp

PURPOSE: High level event register handler.

CLASSES:
	EventRegisterHandler: handler for the event register system.

DESCRIPTION:
	This class acts like an iterator. Provide a unirofm interface to access the low level "container".

USAGE:
	EventRegisterHandler erh{address_of_event_register_system};

	auto next_event = erh.ExtractEvent();

*/

#include "Gargantua/Event/EventRegisterManager.hpp"
#include "Gargantua/Types.hpp"
#include "Gargantua/Event/BaseEvent.hpp"

#include <ranges>

namespace Gargantua
{
	namespace Event
	{
		//This class manipulates the event queue performing basic operations (like extract, filter, ecc).
		class EventRegisterHandler
		{
		public:
			EventRegisterHandler(SharedRes<EventRegisterManager>);

			//TODO: maybe is better to return a std::optional?
			UniqueRes<BaseEvent> ExtractEvent();

			SharedRes<EventRegisterManager> GetEventRegisterSystem() { return hdl; }

			void SetEventRegisterSystem(SharedRes<EventRegisterManager> ers)
			{
				hdl = ers;
			}

			auto GetViewOfEvents()
			{
				return hdl->event_queue | std::views::all;
			}

			void ClearEventQueue()
			{
				hdl->event_queue.clear();
			}

		private:
			SharedRes<EventRegisterManager> hdl;
		};
	} //namespace Event
} //namespace Gargantua