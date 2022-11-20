/*
gargantua/memory/mallocator.ixx

PURPOSE: Interface for low level memory.

CLASSES:
	Mallocator: Provides a base allocator that uses malloc, free and realloc.

DESCRIPTION:
	


USAGE:
	Mallocator m;

	void* a = m.Allocate(16); //allocate 16 bytes.

	...

	m.Deallocate(a); //remember to deallocate memory.

*/

export module gargantua.memory.mallocator;

import <cstdlib>;
import <string_view>;

import gargantua.types;

export namespace gargantua::memory
{
	class Mallocator
	{
	public:

		/*
		* Allocate memory using std::malloc.
		*/
		auto Allocate(natural64_t size) -> void*
		{
			return std::malloc(size);
		}


		/*
		* Deallocate memory using std::free.
		*/
		auto Deallocate(void* p) -> void
		{
			std::free(p);
		}


		/*
		* Reallocate memory using std::realloc.
		*/
		auto Reallocate(void* p, natural64_t new_size) -> void*
		{
			return std::realloc(p, new_size);
		}


		auto GetName() -> std::string_view;


	}; //class Mallocator
} //namespace gargantua::memory