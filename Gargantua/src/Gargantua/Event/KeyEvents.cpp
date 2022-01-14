#include "KeyEvents.hpp"


namespace Gargantua
{
	namespace Event
	{
		const BaseEvent::event_name_t KeyEvent::EventName{ "KeyEvent" };
		const BaseEvent::event_name_t KeyPressedEvent::EventName{ "KeyPressedEvent" };
		const BaseEvent::event_name_t KeyReleasedEvent::EventName{ "KeyReleasedEvent" };
	} //namespace Event
} //namespace Gargantua