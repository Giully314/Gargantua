#include "MouseEvents.hpp"


namespace Gargantua
{
	namespace Event
	{
		const BaseEvent::event_name_t MouseCursorEvent::EventName{ "MouseCursorEvent" };
		const BaseEvent::event_name_t MouseButtonEvent::EventName{ "MouseButtonEvent" };
		const BaseEvent::event_name_t MouseButtonPressedEvent::EventName{ "MouseButtonPressedEvent" };
		const BaseEvent::event_name_t MouseButtonReleasedEvent::EventName{ "MouseButtonReleasedEvent" };
	} //namespace Event
} //namespace Gargantua