/*
Gargantua/Event/MouseEvents.cpp
*/
#include "MouseEvents.hpp"


namespace Gargantua
{
	namespace Event
	{
		const event_name_t MouseCursorEvent::EventName{ "MouseCursorEvent" };
		const event_name_t MouseButtonEvent::EventName{ "MouseButtonEvent" };
		const event_name_t MouseButtonPressedEvent::EventName{ "MouseButtonPressedEvent" };
		const event_name_t MouseButtonReleasedEvent::EventName{ "MouseButtonReleasedEvent" };
	} //namespace Event
} //namespace Gargantua