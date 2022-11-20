/*
gargantua/generators/limits_generator.ixx


PURPOSE: Various tags for generators.

CLASSES:
	UniqueGenerator: generates unique elements.
	MonotonicGenerator: generates elements in a monotonic way.
	MonotonicIncreasingGenerator: every element is greater than the previous.
	MonotonicDecreasingGenerator: every element is smaller than the previous.


DESCRIPTION:


USAGE:


TODO:
	add tags for positive/negative numbers only?

*/

export module gargantua.generator.generator_tags;

export namespace gargantua::generator
{

	struct UniqueGeneratorTag { };
	struct MonotonicGeneratorTag : UniqueGeneratorTag {};
	struct MonotonicIncreasingGeneratorTag : MonotonicGeneratorTag {};
	struct MonotonicDecreasingGeneratorTag : MonotonicGeneratorTag {};

} //namespace gargantua::generator
