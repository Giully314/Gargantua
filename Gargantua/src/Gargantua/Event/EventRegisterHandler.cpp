#include "EventRegisterHandler.hpp"


namespace Gargantua
{
	namespace Event
	{
		EventRegisterHandler::EventRegisterHandler(NonOwnedRes<EventRegisterSystem> event_reg_sys) : hdl(event_reg_sys)
		{

		}


		UniqueRes<BaseEvent> EventRegisterHandler::ExtractEvent()
		{
			if (hdl->event_queue.empty())
			{
				return nullptr;
			}

			UniqueRes<BaseEvent> e = std::move(hdl->event_queue.front());
			hdl->event_queue.pop_front();
			return e;
		}
	} //namespace Event
} //namespace Gargantua