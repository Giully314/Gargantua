/*
* gargantua/generator/sequential_generator.ixx
* 
* PURPOSE:
* 
* CLASSES:
* 
* DESCRIPTION:
* 
* TODO:
*	- Add check of overflow.
* 
* USAGE:
* 
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
