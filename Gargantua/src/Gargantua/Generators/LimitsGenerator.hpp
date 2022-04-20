#pragma once
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

#include <limits>

namespace Gargantua
{
	namespace Generators
	{
		template <typename T>
		class LimitsGenerator
		{
		public:
			inline static constexpr T MaxGenerableValue() noexcept 
			{
				return std::numeric_limits<T>::max();
			}


			inline static constexpr T MinGenerableValue() noexcept
			{
				return std::numeric_limits<T>::min();
			}
		};
	} //namespace Generators 
} //namespace Gargantua


