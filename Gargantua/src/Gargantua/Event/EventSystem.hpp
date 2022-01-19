#pragma once

#include "Gargantua/Core/EngineLogger.hpp"

#include "Gargantua/Event/BaseEvent.hpp"
#include "Gargantua/Types.hpp"
#include "Gargantua/Concepts/Event.hpp"
#include "Gargantua/Event/EventListenerHandler.hpp"
#include "Gargantua/Event/EventRegisterHandler.hpp"


#include <queue>
#include <unordered_map>
#include <functional>
#include <vector>
#include <algorithm>
#include <ranges>


namespace Gargantua
{
	namespace Event
	{
		/*
		Simple event dispatch based on a queue. The events are registered and processed later. 
		A system can register a function that is executed when a particular type of event is processed.
		TODO: Add the possilibity to register a blocking event.
		*/

		using event_callback_t = std::function<void(const BaseEvent&)>;


		class EventSystem
		{
		public:
			EventSystem();

			inline NonOwnedRes<EventRegisterSystem> GetEventRegisterSystem() 
			{ 
				return event_reg_sys.get();
			}

			inline NonOwnedRes<EventListenerSystem> GetEventListenerSystem()
			{
				return event_list_sys.get();
			}

			void ProcessEvents();
			

		private:
			UniqueRes<EventRegisterSystem> event_reg_sys;
			UniqueRes<EventListenerSystem> event_list_sys;
			
			UniqueRes<EventRegisterHandler> event_reg_hdl;
			UniqueRes<EventListenerHandler> event_list_hdl;
		};
	} //namespace Event
} //namespace Gargantua

