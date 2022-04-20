#pragma once
/*
Gargantua/Generators/LimitsGenerator.hpp


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

namespace Gargantua
{
	namespace Generators
	{
		struct UniqueGenerator { };
		struct MonotonicGenerator : UniqueGenerator {};
		struct MonotonicIncreasingGenerator : MonotonicGenerator {};
		struct MonotonicDecreasingGenerator : MonotonicGenerator {};
		
	} //namespace Generators 
} //namespace Gargantua