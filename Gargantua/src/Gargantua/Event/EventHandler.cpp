#include "EventHandler.hpp"


namespace Gargantua
{
	namespace Event
	{

		void EventHandler::ProcessEvents()
		{
			while (!event_queue.empty())
			{
				UniqueRes<BaseEvent> e = std::move(event_queue.front());
				event_queue.pop();

				ProcessEvent(*e);
			}
		}


		void EventHandler::ProcessEvent(const BaseEvent& event)
		{
			for (auto& hdl : callbacks[event.GetEventName()])
			{
				hdl.f(event);
			}
		}
	} //namespace Event
} //namespace Gargantua
