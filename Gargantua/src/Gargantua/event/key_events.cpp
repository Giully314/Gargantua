/*
gargantua/event/key_events.cpp
*/

module gargantua.event.key_events;


namespace gargantua::event
{
	const event_name_t KeyEvent::EventName{ "KeyEvent" };
	const event_name_t KeyPressedEvent::EventName{ "KeyPressedEvent" };
	const event_name_t KeyReleasedEvent::EventName{ "KeyReleasedEvent" };
} //namespace gargantua::event