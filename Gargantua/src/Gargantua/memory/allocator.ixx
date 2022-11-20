/*
gargantua/memory/allocator.ixx
	
*/

export module gargantua.memory.allocator;

import <string>;
import <string_view>;

import gargantua.types;




export namespace gargantua::memory
{
	template <typename T>
	concept Allocator = true;


	class BaseAllocator
	{
	public:
		BaseAllocator() = default;
		BaseAllocator(const std::string& name_) : name(name_) { }

		virtual ~BaseAllocator() = default;

		virtual auto Allocate(natural64_t size, natural64_t alignment) -> void* = 0;
		
		virtual auto Deallocate(void* memory) -> void = 0;

		


		auto GetName() const noexcept -> std::string_view
		{
			return name;
		}

		auto GetNumberOfAllocations() const noexcept -> natural64_t
		{
			return num_of_allocations;
		}

	protected:
		std::string name{"BaseAllocator"};
		natural64_t num_of_allocations{ 0 };
	};

} //namespace gargantua::memory