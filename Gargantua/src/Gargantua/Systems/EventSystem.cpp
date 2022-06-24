/*
Gargantua/Systems/EventSystem.cpp
*/
#include "EventSystem.hpp"

#include <algorithm>
#include <ranges>


namespace Gargantua
{
	namespace Systems
	{
		EventSystem::EventSystem() : block_input_events(false)
		{
			event_reg_mng = CreateSharedRes<Event::EventRegisterManager>();
			event_list_mng = CreateSharedRes<Event::EventListenerManager>();

			event_reg_hdl = CreateSharedRes<Event::EventRegisterHandler>(event_reg_mng);
			event_list_hdl = CreateSharedRes<Event::EventListenerHandler>(event_list_mng);
		}


		void EventSystem::ProcessEvents()
		{	
			auto events = event_reg_hdl->GetViewOfEvents() | 
				std::views::filter([&](UniqueRes<Event::BaseEvent>& e) //block input event if activated
				{
					return !(block_input_events && (e->static_type == Event::StaticEventType::MouseEvent ||
						e->static_type == Event::StaticEventType::KeyboardEvent));
				});


			std::ranges::for_each(events, [&](auto& e)
				{
					const auto& event_name = e->GetEventName();

					auto callbacks = event_list_hdl->GetEventListeners(event_name);

					std::ranges::for_each(callbacks, [&](auto& callback)
						{
							callback(*e);
						});
				});


			event_reg_hdl->ClearEventQueue();
		}
	} //namespace Systems
} //namespace Gargantua
