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

#include "Gargantua/Types.hpp"

#include "Gargantua/Concepts/Event.hpp"

#include "Gargantua/Event/BaseEvent.hpp"
#include "Gargantua/Event/EventListenerHandler.hpp"
#include "Gargantua/Event/EventRegisterHandler.hpp"
#include "Gargantua/Event/EventRegisterManager.hpp"
#include "Gargantua/Event/EventListenerManager.hpp"


#include <functional>
#include <utility>


namespace Gargantua
{
	namespace Systems
	{
		using event_callback_t = std::function<void(const Event::BaseEvent&)>;


		class EventSystem
		{
		public:
			EventSystem();


			void BlockInputEvents(bool block)
			{
				block_input_events = block;
			}

			void ProcessEvents();
			

			template <Concepts::Event T, typename ...Args>
			void RegisterEvent(Args&& ...args)
			{
				event_reg_mng->RegisterEvent<T, Args...>(std::forward<Args>(args)...);
			}


			template <Concepts::Event T>
			natural_t RegisterListener(event_callback_t f)
			{
				return event_list_mng->RegisterListener<T>(std::move(f));
			}

			template <Concepts::Event T>
			void UnregisterListener(natural_t id)
			{
				event_list_mng->UnregisterListener(id);
			}


		private:
			SharedRes<Event::EventRegisterManager> event_reg_mng;
			SharedRes<Event::EventListenerManager> event_list_mng;

			SharedRes<Event::EventRegisterHandler> event_reg_hdl;
			SharedRes<Event::EventListenerHandler> event_list_hdl;

			/*
			For example, if the panel in which the app is running is not in focus, block the process of input events 
			(like key pressed and mouse events) even though they are registered by the backend.
			*/
			bool block_input_events;
		};
	} //namespace Systems
} //namespace Gargantua

