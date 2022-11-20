/*
gargantua/event/window_events.cpp
*/

module gargantua.event.window_events;


namespace gargantua::event
{
	const event_name_t WindowEvent::EventName{ "WindowEvent" };
	const event_name_t WindowResizeEvent::EventName{ "WindowResizeEvent" };
	const event_name_t WindowCloseEvent::EventName{ "WindowCloseEvent" };
} //namespace gargantua::event