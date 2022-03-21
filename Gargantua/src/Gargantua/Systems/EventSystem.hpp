#pragma once
/*
Gargantua/Systems/EventSystem.hpp

PURPOSE: Event system.


CLASSES:
	EventSystem: Event system using the Event components.


DESCRIPTION:
	Simple event dispatch based on a queue. The events are registered and processed later.
	A system can register a function that is executed when a particular type of event is processed.


TODO: Add the possilibity to register a blocking event or make another class to do that.

*/

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
	namespace Systems
	{
		using event_callback_t = std::function<void(const Event::BaseEvent&)>;


		class EventSystem
		{
		public:
			EventSystem();

			inline NonOwnedRes<Event::EventRegisterSystem> GetEventRegisterSystem() 
			{ 
				return event_reg_sys.get();
			}

			inline NonOwnedRes<Event::EventListenerSystem> GetEventListenerSystem()
			{
				return event_list_sys.get();
			}

			void ProcessEvents();
			

		private:
			UniqueRes<Event::EventRegisterSystem> event_reg_sys;
			UniqueRes<Event::EventListenerSystem> event_list_sys;
			
			UniqueRes<Event::EventRegisterHandler> event_reg_hdl;
			UniqueRes<Event::EventListenerHandler> event_list_hdl;
		};
	} //namespace Systems
} //namespace Gargantua

