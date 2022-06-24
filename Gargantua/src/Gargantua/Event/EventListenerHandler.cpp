/*
Gargantua/Event/EventListenerHandler.cpp
*/
#include "EventListenerHandler.hpp"


namespace Gargantua
{
	namespace Event
	{
		EventListenerHandler::EventListenerHandler(SharedRes<EventListenerManager> event_list_sys) :
			hdl(event_list_sys)
		{

		}
	} //namespace Event
} //namespace Gargantua