/*
gargantua/event/event_concepts.ixx

PURPOSE: Compile time checks for Event types.

CLASSES:
	Event: Concept to check compile time properties of an Event.

DESCRIPTION:
	Check if the type of a template parameter is an Event.

USAGE:
	template <Gargantua::Concepts::Event MyTypeEvent> void func();
*/

export module gargantua.event.event_concepts;

import <concepts>;
import <string>;

import gargantua.event.base_event;

export namespace gargantua::event
{
	template <typename T>
	concept Event = std::derived_from<T, BaseEvent> &&
		requires(T e)
	{
		{T::EventName} -> std::convertible_to<std::string>;
	};
} //namespace gargantua::event