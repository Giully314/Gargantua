#pragma once

#include "Gargantua/Concepts/Event.hpp"
#include "Gargantua/Event/EventListenerSystem.hpp"
#include "Gargantua/Types.hpp"

#include <ranges>
#include <string>


namespace Gargantua
{
	namespace Event
	{
		class EventListenerHandler
		{
		public:
			EventListenerHandler(NonOwnedRes<EventListenerSystem>);


			auto GetEventListeners(const event_name_t& event_name)
			{
				return hdl->callbacks[event_name] | std::views::values;
			}

			auto GetEventListeners()
			{
				return hdl->callbacks | std::views::all;
			}


			inline NonOwnedRes<EventListenerSystem> GetEventListenerSystem() { return hdl; }
			
			inline void SetEventListenerSystem(NonOwnedRes<EventListenerSystem> els)
			{
				hdl = els;
			}

		private:
			NonOwnedRes<EventListenerSystem> hdl;
		};
	} //namespace Event
} //namespace Gargantua



