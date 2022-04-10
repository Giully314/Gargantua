#pragma once
/*
Gargantua/Concepts/Event.hpp

PURPOSE: Compile time checks for Event types.

CLASSES:
	Event: Concept to check compile time properties of an Event.

DESCRIPTION:
	Check if the type of a template parameter is an Event.

USAGE:
	template <Gargantua::Concepts::Event MyTypeEvent> void func();
*/

#include "Gargantua/Event/BaseEvent.hpp"


#include <concepts>
#include <string>

namespace Gargantua
{
	namespace Concepts
	{
		template <typename T>
		concept Event = std::derived_from<T, Event::BaseEvent> &&
			requires(T e)
		{
			{T::EventName} -> std::convertible_to<std::string>;
		};
	}
}