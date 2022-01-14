#pragma once

#include <concepts>
#include <string>

namespace Gargantua
{
	namespace Event
	{
		struct BaseEvent;
	}

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