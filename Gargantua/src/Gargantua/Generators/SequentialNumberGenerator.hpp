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

	auto n = gen.Get(); //n = 0
	n = gen.Get(); //n = 1
	n = gen.Get(); //n = 2


	while (n < gen.MaxGenerableValue())
	{
		//do stuff
	}
*/

#include "Gargantua/Generators/LimitsGenerator.hpp"
#include "Gargantua/Generators/Tags.hpp"

#include <concepts>
#include <iterator>


namespace Gargantua
{
	namespace Generators
	{
		template <typename T> 
		requires std::unsigned_integral<T> && std::incrementable<T>
		class SequentialNumberGenerator : public LimitsGenerator<T>
		{
		public:
			using TagGenerator = MonotonicIncreasingGenerator;
			using ValueType = T;


			ValueType Get()
			{
				return n++;
			}


		private:
			ValueType n{ 0 };
		};
	} //namespace Generators 
} //namespace Gargantua