/*
* gargantua/event/event_concepts.ixx
* 
* PURPOSE: concepts for the event package.
* 
* CONCEPTS:
*	CEvent: check if a type is derived from BaseEvent (required to be identified as event).
*/

export module gargantua.event.concepts;

import <concepts>;

import gargantua.event.base_event;

export namespace gargantua::event
{
	template <typename T>
	concept CEvent = std::derived_from<T, BaseEvent>;
} // namespace gargantua::event