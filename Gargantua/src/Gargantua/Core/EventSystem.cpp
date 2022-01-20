#include "EventSystem.hpp"


namespace Gargantua
{
	namespace Core
	{
		EventSystem::EventSystem()
		{
			event_reg_sys = CreateUniqueRes<Event::EventRegisterSystem>();
			event_list_sys = CreateUniqueRes<Event::EventListenerSystem>();

			event_reg_hdl = CreateUniqueRes<Event::EventRegisterHandler>(event_reg_sys.get());
			event_list_hdl = CreateUniqueRes<Event::EventListenerHandler>(event_list_sys.get());
		}


		void EventSystem::ProcessEvents()
		{
			GRG_CORE_DEBUG("Start Process Events");
			auto events = event_reg_hdl->GetViewOfEvents();
			
			for (auto& e : events)
			{
				const auto& event_name = e->GetEventName();
				GRG_CORE_DEBUG("Process {}", event_name);
				auto callbacks = event_list_hdl->GetEventListeners(event_name);
				for (auto& callback : callbacks)
				{
					callback(*e);
				}
			}

			event_reg_hdl->ClearEventQueue();

			GRG_CORE_DEBUG("End Process Events");
		}
	} //namespace Event
} //namespace Gargantua
