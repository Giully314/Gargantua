#pragma once
/*
Gargantua/Concepts/Generator.hpp

PURPOSE: Compile time checks for generators.

CLASSES:
	Generator: basic concept for a generator.
	UniqueGenerator: concept for generators with UniqueGenerator tag.
	MonotonicGenerator: concept for generators with MonotonicGenerator tag.
	MonotonicIncreasingGenerator: concept for generators with MonotonicIncreasingGenerator tag.
	MonotonicDecreasingGenerator: concept for generators with MonotonicDecreasingGenerator tag.

DESCRIPTION:
	These concepts are used for checking if a generator has the properties that make it so.

USAGE:
	template <UniqueGenerator TGenerator>
	int GenerateID(...);

*/

#include "Gargantua/Generators/Tags.hpp"

#include <concepts>
#include <type_traits>

namespace Gargantua
{
	namespace Concepts
	{

		template <typename T>
		concept Generator = requires (T g)
		{
			typename T::TagGenerator;
			typename T::ValueType;

			{g.Get()} -> std::convertible_to<typename T::ValueType>;
			{g.MaxGenerableValue()} -> std::convertible_to<typename T::ValueType>;
			{g.MinGenerableValue()} -> std::convertible_to<typename T::ValueType>;
		};


		/*template <typename T>
		concept NumericGenerator = Generator<T> && requires (T g)
		{
			{g.MaxGenerableValue()} -> std::same_as<T>;
			{g.MinGenerableValue()} -> std::same_as<T>;
		};*/
		

		template <typename T>
		concept UniqueGenerator = Generator<T> && 
			std::same_as<typename T::TagGenerator, Generators::UniqueGenerator>;

		template <typename T>
		concept MonotonicGenerator = Generator<T> && 
			std::is_base_of_v<Generators::MonotonicGenerator, typename T::TagGenerator>;

		template <typename T>
		concept MonotonicIncreasingGenerator = Generator<T> && 
			std::same_as<Generators::MonotonicIncreasingGenerator, typename T::TagGenerator>;

		template <typename T>
		concept MonotonicDecreasingGenerator = Generator<T> &&
			std::same_as<Generators::MonotonicDecreasingGenerator, typename T::TagGenerator>;


	} //namespace Concepts 
} //namespace Gargantua