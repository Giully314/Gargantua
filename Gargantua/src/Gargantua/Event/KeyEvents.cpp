/*
Gargantua/Event/KeyEvents.cpp
*/
#include "KeyEvents.hpp"


namespace Gargantua
{
	namespace Event
	{
		const event_name_t KeyEvent::EventName{ "KeyEvent" };
		const event_name_t KeyPressedEvent::EventName{ "KeyPressedEvent" };
		const event_name_t KeyReleasedEvent::EventName{ "KeyReleasedEvent" };
	} //namespace Event
} //namespace Gargantua