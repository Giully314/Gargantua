/*
* gargantua/generator/sequential_generator.ixx
* 
* PURPOSE: Natural number generator.
* 
* CLASSES:
*	SequentialGenerator: generate a sequence of numbers, starting from 0.
*
* TODO:
*	- Add check of overflow.
*	- Use the generator class.
* 
* USAGE:
*	SequentialGenerator<int> sq;
*	int i = sq.Next(); // 0
*	i = sq.Next(); // 1
*/


export module gargantua.generator.sequential_generator;

import <concepts>;


namespace gargantua::generator
{
	export
	template <std::unsigned_integral T>
	class SequentialGenerator
	{
	public:
		using ValueType = T;

		// Get the next value. 
		auto Next() -> ValueType
		{
			return current_value++;
		}

	private:
		T current_value{ 0 };
	};
} // namespace gargantua::generator
