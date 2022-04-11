/*
Gargantua/Systems/EventSystem.cpp
*/
#include "EventSystem.hpp"


namespace Gargantua
{
	namespace Systems
	{
		EventSystem::EventSystem()
		{
			event_reg_mng = CreateUniqueRes<Event::EventRegisterManager>();
			event_list_mng = CreateUniqueRes<Event::EventListenerManager>();

			event_reg_hdl = CreateUniqueRes<Event::EventRegisterHandler>(event_reg_mng.get());
			event_list_hdl = CreateUniqueRes<Event::EventListenerHandler>(event_list_mng.get());
		}


		void EventSystem::ProcessEvents()
		{
			auto events = event_reg_hdl->GetViewOfEvents();
			
			for (auto& e : events)
			{
				const auto& event_name = e->GetEventName();
				//GRG_CORE_INFO("Processing event {}", event_name);
				auto callbacks = event_list_hdl->GetEventListeners(event_name);
				for (auto& callback : callbacks)
				{
					callback(*e);
				}
			}

			event_reg_hdl->ClearEventQueue();
		}
	} //namespace Systems
} //namespace Gargantua
