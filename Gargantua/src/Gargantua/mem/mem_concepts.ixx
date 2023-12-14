/*
* gargantua/mem/mem_concepts.ixx
* 
* PURPOSE: Provide concepts for memory allocators.
* 
* CONCEPTS:
*	CAllocator: concept based on allocator requirements defined by C++.
* 
* DESCRIPTION:
*/

export module gargantua.mem.concepts;

import <concepts>;

export namespace gargantua::mem
{
	// TODO: requirements from: https://en.cppreference.com/w/cpp/named_req/Allocator
	template <typename T>
	concept CAllocator = requires (T a, typename T::value_type* p, size_t n)
	{
		typename T::value_type;
		{a.allocate(n)} -> std::same_as<typename T::value_type*>;
		{a.deallocate(p, n)} -> std::same_as<void>;
	};
} // namespace gargantua::mem