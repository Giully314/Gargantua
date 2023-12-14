/*
* gargantua/generator/gen_sequentialgenerator.ixx
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


export module gargantua.gen.sequential_generator;

import <concepts>;


namespace gargantua::gen
{
	export template <std::unsigned_integral T>
	class SequentialGenerator
	{
	public:
		// Get the next value. 
		constexpr auto Next() -> T
		{
			return current_value++;
		}

	private:
		T current_value{ 0 };
	};
} // namespace gargantua::gen
