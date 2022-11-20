/*
gargantua/generator/natural_number_generator.ixx

PURPOSE: Generator for natural numbers.

CLASSES:
	NaturalNumberGenerator: Generate sequential natural numbers.

DESCRIPTION:
	Generate natural numbers in an increasing monotonic way.

USAGE:
	NaturalNumberGenerator<unsigned int> gen{1729};

	auto n = gen.Get(); //n = 1729
	n = gen.Get(); //n = 1730
	n = gen.Get(); //n = 1731


	while (n < gen.MaxGenerableValue())
	{
		//do stuff
	}
*/

export module gargantua.generator.natural_number_generator;

import <concepts>;
import <iterator>;

import gargantua.generator.limits_generator;
import gargantua.generator.generator_tags;


export namespace gargantua::generator
{

	template <typename T>
		requires std::unsigned_integral<T> && std::incrementable<T>
	class NaturalNumberGenerator : public LimitsGenerator<T>
	{
	public:
		using TagGenerator = MonotonicIncreasingGeneratorTag;
		using ValueType = T;


		/*
		* Construct the generator with the number 0 as start.
		*/
		constexpr NaturalNumberGenerator() = default;

		/*
		* Construct a generator that starts with the given number.
		*/
		constexpr NaturalNumberGenerator(T start) : n(start)
		{

		}

		/*
		* Get the next number. 
		* Note that it is responsability of the caller to check possible overflow.
		*/
		[[nodiscard]]
		constexpr auto Get() -> T
		{
			return n++;
		}


	private:
		T n{ 0 };
	}; //class NaturalNumberGenerator

} //namespace gargantua::generator
