/*
gargantua/system/event_system.cpp
*/

module gargantua.system.event_system;

import <algorithm>;
import <ranges>;



namespace gargantua::system
{

	auto EventSystem::ProcessEvents() -> void
	{
		auto& event_queue = event_reg_mng.GetCurrentEventQueue();
		
		/*
		* Swap queue so that the new events created are not processed in this frame.
		*/
		event_reg_mng.SwapQueue(); 


		std::ranges::for_each(event_queue,
			[&](event::BaseEvent& e)
			{
				auto listeners_view = event_list_mng.GetListenersView(e.GetEventName());
				
				for (auto& l : listeners_view)
				{
					l(e);
				}
			}, 
			[](UniqueRes<event::BaseEvent>& e) -> event::BaseEvent&
			{
				return *e;
			});

		event_queue.clear();
	}

} //namespace gargantua::system
