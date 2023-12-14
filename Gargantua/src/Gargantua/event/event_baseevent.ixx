/*
* gargantua/event/event_baseevent.ixx
* 
* PURPOSE: define the building block for custom events.
* 
* CLASSES:
*	BaseEvent: base class for all the events.
* 
* 
* DESCRIPTION:
*	Each custom event must inherit from the BaseEvent struct to be identified as event inside the engine.
*/

export module gargantua.event.base_event;

export namespace gargantua::event
{
	struct BaseEvent 
	{
		constexpr explicit BaseEvent() = default;
	};
} // namespace gargantua::event
