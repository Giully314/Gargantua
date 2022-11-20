/*
gargantua/event/mouse_events.cpp
*/

module gargantua.event.mouse_events;


namespace gargantua::event
{
	const event_name_t MouseEvent::EventName{ "MouseEvent" };
	const event_name_t MouseCursorEvent::EventName{ "MouseCursorEvent" };
	const event_name_t MouseButtonEvent::EventName{ "MouseButtonEvent" };
	const event_name_t MouseButtonPressedEvent::EventName{ "MouseButtonPressedEvent" };
	const event_name_t MouseButtonReleasedEvent::EventName{ "MouseButtonReleasedEvent" };
	const event_name_t MouseWheelScrollEvent::EventName{ "MouseWheelScrollEvent" };
} //namespace gargantua::event