#pragma once
/*
Gargantua/Generators/SequentialNumberGenerator.hpp

PURPOSE: Generate sequential numbers.

CLASSES:
	SequentialNumberGenerator: Get consecutive numbers.

DESCRIPTION:
	Simple utility class for generate sequential numbers.

USAGE:
	SequentialNumberGenerator<int> gen;

	gen.Get();
*/

#include <concepts>
#include <iterator>


namespace Gargantua
{
	namespace Generators
	{
		template <typename T> 
		requires std::unsigned_integral<T> && std::incrementable<T>
		class SequentialNumberGenerator
		{
		public:
			T Get()
			{
				return n++;
			}

		private:
			T n{ 0 };
		};
	}
}