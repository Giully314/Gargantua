/*
* gargantua/event/event_engineeventdispatcher.ixx
* 
* PURPOSE: provide a global access to the low level event dispatcher.
* 
* DESCRIPTION:
*	The EngineEventDispatcher returns a static EventDispatcher used by the systems to listen or dispatch
*	low level events like window events, input events, audio.
*/

export module gargantua.event.engine_event_dispatcher;

import gargantua.event.event_dispatcher;

namespace gargantua::event
{
	export inline auto EngineEventDispatcher() -> EventDispatcher&
	{
		static EventDispatcher ed;
		return ed;
	}
} // namespace gargantua::event