/*
* gargantua/math/math_concepts.ixx
* 
* PURPOSE: define math concepts.
* 
* CONCEPTS:
*	CIsArithmetic: Check if a type is an arithmetic type (integral or floating).
*/

export module gargantua.math.concepts;

import <type_traits>;

export namespace gargantua::math
{
	template <typename T>
	concept CIsArithmetic = std::is_arithmetic_v<T>;
} // namespace gargantua::math