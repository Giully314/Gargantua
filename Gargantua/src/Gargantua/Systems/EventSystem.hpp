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
#include "Gargantua/Event/EventRegisterManager.hpp"
#include "Gargantua/Event/EventListenerManager.hpp"


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

			inline NonOwnedRes<Event::EventRegisterManager> GetEventRegisterManager() 
			{ 
				return event_reg_mng.get();
			}

			inline NonOwnedRes<Event::EventListenerManager> GetEventListenerManager()
			{
				return event_list_mng.get();
			}

			void ProcessEvents();
			

		private:
			UniqueRes<Event::EventRegisterManager> event_reg_mng;
			UniqueRes<Event::EventListenerManager> event_list_mng;
			
			UniqueRes<Event::EventRegisterHandler> event_reg_hdl;
			UniqueRes<Event::EventListenerHandler> event_list_hdl;
		};
	} //namespace Systems
} //namespace Gargantua

