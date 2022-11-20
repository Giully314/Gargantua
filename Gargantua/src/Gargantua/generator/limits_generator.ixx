/*
Gargantua/Generators/LimitsGenerator.hpp


PURPOSE: Numerical limits of a generator.

CLASSES:
	LimitsGenerator: Get the limits for a generator.

DESCRIPTION:
	This class should be used as a base class for simple generators that use numerical types
	to automatically get the upper and lower limit of the type representability.

USAGE:
	LimitsGenerator<int>::MaxGenerableValue();

TODO:
	add a concept to check type compatibility at compile time?
*/

export module gargantua.generator.limits_generator;

import <limits>;

export namespace gargantua::generator
{

	export template <typename T>
	class LimitsGenerator
	{
	public:
		static constexpr auto MaxGenerableValue() noexcept -> T
		{
			return std::numeric_limits<T>::max();
		}


		static constexpr auto MinGenerableValue() noexcept -> T
		{
			return std::numeric_limits<T>::min();
		}
	}; //class LimitsGenerator

} //namespace gargantua::generator


