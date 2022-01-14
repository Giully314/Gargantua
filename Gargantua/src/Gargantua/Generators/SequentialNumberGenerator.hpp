#pragma once

#include <concepts>
#include <iterator>


namespace Gargantua
{
	namespace Generators
	{
		/*
		Simple utility class for generate sequential numbers.
		*/
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