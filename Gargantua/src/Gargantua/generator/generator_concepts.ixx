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

export module gargantua.generator.generator_concepts;

import <concepts>;
import <type_traits>;

import gargantua.generator.generator_tags;


export namespace gargantua::generator
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
		std::same_as<typename T::TagGenerator, UniqueGeneratorTag>;

	template <typename T>
	concept MonotonicGenerator = Generator<T> &&
		std::is_base_of_v<MonotonicGeneratorTag, typename T::TagGenerator>;

	template <typename T>
	concept MonotonicIncreasingGenerator = Generator<T> &&
		std::same_as<MonotonicIncreasingGeneratorTag, typename T::TagGenerator>;

	template <typename T>
	concept MonotonicDecreasingGenerator = Generator<T> &&
		std::same_as<MonotonicDecreasingGeneratorTag, typename T::TagGenerator>;

} //namespace gargantua::generator