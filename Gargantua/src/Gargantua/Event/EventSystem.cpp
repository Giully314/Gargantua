#include "EventSystem.hpp"


namespace Gargantua
{
	namespace Event
	{
		EventSystem::EventSystem()
		{
			event_reg_sys = CreateUniqueRes<EventRegisterSystem>();
			event_list_sys = CreateUniqueRes<EventListenerSystem>();

			event_reg_hdl = CreateUniqueRes<EventRegisterHandler>(event_reg_sys.get());
			event_list_hdl = CreateUniqueRes<EventListenerHandler>(event_list_sys.get());
		}


		void EventSystem::ProcessEvents()
		{
			GRG_CORE_DEBUG("Start Process Events");
			auto events = event_reg_hdl->GetViewOfEvents();
			
			for (auto& e : events)
			{
				auto callbacks = event_list_hdl->GetEventListeners(e->GetEventName());
				for (auto& callback : callbacks)
				{
					callback(*e);
				}
			}

			event_reg_hdl->ClearEventQueue();
		}
	} //namespace Event
} //namespace Gargantua
