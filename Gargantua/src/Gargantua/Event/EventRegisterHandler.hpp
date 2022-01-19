#pragma once

#include "Gargantua/Event/EventRegisterSystem.hpp"
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
			EventRegisterHandler(NonOwnedRes<EventRegisterSystem>);

			//TODO: maybe is better to return a std::optional?
			UniqueRes<BaseEvent> ExtractEvent();

			inline NonOwnedRes<EventRegisterSystem> GetEventRegisterSystem() { return hdl; }

			inline void SetEventRegisterSystem(NonOwnedRes<EventRegisterSystem> ers)
			{
				hdl = ers;
			}

			inline auto GetViewOfEvents()
			{
				return hdl->event_queue | std::views::all;
			}

			inline void ClearEventQueue()
			{
				hdl->event_queue.clear();
			}

		private:
			NonOwnedRes<EventRegisterSystem> hdl;
		};
	} //namespace Event
} //namespace Gargantua