/*
* gargantua/ds/ds_sparseset.ixx
* 
* PURPOSE: Implementation of sparse set.
* 
* CLASSES: 
* 	SparseSet: data structure used primarily by ecs for fast insert/delete and traverse components.
* 
* DESCRIPTION:
* 	The implementation is based on this article:
* 	https://www.codeproject.com/Articles/859324/Fast-Implementations-of-Sparse-Sets-in-Cplusplus
* 		
* 	The implementation is done by trying to respect the syntax of STL containers.
* 
* 	Note that the SparseSet uses the maximum of the type as a null value to avoid double memory ref to check
* 	if an element is in the set.
* 
* 
* USAGE:
* 	SparseSet<unsigned int> s;
* 	s.insert(2);
* 	
* 	//Fast iteration for all the packed data.
* 	//Note: iterators are not preserved after insert or erase.
* 	for (auto& p : s)
* 	{
* 		//DON'T INSERT OR REMOVE IN A RANGE-BASED LOOP OR WHILE USING ITERATORS.
* 		...
* 	}
* 	
* 	s.erase(2);
* 
* TODO:
* 	- write a custom iterator (useful for sorting).
* 	- satisfy the container allocator aware requirements.
*	- assuming the max value representable by T as a null value could not be a good approach.
*/

export module gargantua.ds.sparse_set;

import <concepts>;
import <memory>;
import <vector>;
import <utility>;
import <cassert>;
import <limits>;

import gargantua.types;

export namespace gargantua::ds
{
	template <std::unsigned_integral T, typename TAlloc = std::allocator<T>>
	class SparseSet
	{
	public:
		// TODO: this section is not completed.
		using value_type = T;
		using reference = T&;
		using const_reference = const T&;
		using iterator = typename std::vector<T, TAlloc>::iterator;
		using const_iterator = typename std::vector<T, TAlloc>::const_iterator;
		using difference_type = typename std::vector<T, TAlloc>::difference_type;
		using size_type = typename std::vector<T, TAlloc>::size_type;


	public:
		constexpr explicit SparseSet() = default;

		SparseSet(const SparseSet&) = default;
		SparseSet& operator=(const SparseSet&) = default;

		SparseSet(SparseSet&&) noexcept = default;
		SparseSet& operator=(SparseSet&&) noexcept = default;

		~SparseSet() = default;


		/*
		* Insert a new value if not present.
		* Complexity: ammortized O(1). Technically the sparse set is resized if the value passed is not in the range.
		*/
		constexpr auto insert(T value) -> void 
		{
			if (!contains(value)) [[likely]]
			{
				try_insert(value);
			}
		}


		/*
		* Erase the value from the set.
		* Complexity: O(1).
		*/
		constexpr auto erase(T value) -> void
		{
			if (contains(value)) [[likely]]
			{
				packed[sparse[value]] = packed.back();
				sparse[packed.back()] = sparse[value];
				sparse[value] = std::numeric_limits<T>::max();
				packed.pop_back();
			}
		}


		/*
		* Return the value at idx in the packed array.
		* No bounds are checked.
		* Complexity: O(1).
		*/
		[[nodiscard]]
		constexpr auto operator[](size_type idx) const -> T
		{
			assert(idx < packed.size());
			return packed[idx];
		}



		/*
		* Return the size of the packed array.
		* Complexity: O(1).
		*/
		[[nodiscard]]
		constexpr auto size() -> size_type
		{
			return packed.size();
		}


		/*
		* Return if the packed array is empty.
		* Complexity: O(1).
		*/
		[[nodiscard]]
		constexpr auto empty() const noexcept -> bool
		{
			return packed.empty();
		}


		/*
		* Check if value is present in the packed array.
		* Complexity: O(1).
		*/
		[[nodiscard]]
		constexpr auto contains(T value) const -> bool
		{
			return value < sparse.size() && sparse[value] != std::numeric_limits<T>::max();
		}


		/*
		* Reserve space for the packed array.
		* Complexity: O(size()) if reallocation is done.
		*/
		constexpr auto reserve(size_type new_capacity) -> void
		{
			packed.reserve(new_capacity);
		}


		/*
		* Return the capacity of the packed array.
		* Complexity: O(1).
		*/
		[[nodiscard]]
		constexpr auto capacity() const noexcept -> size_type
		{
			return packed.capacity();
		}



		/*
		* Swap the sparse set.
		* Complexity: O(1).
		*/
		constexpr auto swap(SparseSet& s) -> void
		{
			using std::swap;
			swap(sparse, s.sparse);
			swap(packed, s.packed);
		}


		/*
		Shrink
		*/
		constexpr auto shrink_to_fit() -> void
		{
			sparse.shrink_to_fit();
			packed.shrink_to_fit();
		}

		
		/*
		Return the index of value in the packed array. If value is not in the sparse set the behavior is undefined.
		Complexity: O(1).
		*/
		[[nodiscard]]
		constexpr auto index_of(const T value) -> size_type
		{
			return sparse[value];
		}


		//********************* ITERATORS FOR PACKED *************************************
		
		[[nodiscard]]
		constexpr auto begin() noexcept -> iterator
		{
			return packed.begin();
		}

		[[nodiscard]]
		constexpr auto end() noexcept -> iterator
		{
			return packed.end();
		}

		[[nodiscard]]
		constexpr auto cbegin() const noexcept -> const_iterator
		{
			return packed.cbegin();
		}

		[[nodiscard]]
		constexpr auto cend() const noexcept -> const_iterator
		{
			return packed.cend();
		}
		
		//********************* ITERATORS FOR PACKED *************************************
		
		


	private:
		using alc_traits = std::allocator_traits<TAlloc>;
		using sparse_container_t = std::vector<typename alc_traits::pointer, typename alc_traits::template rebind_alloc<typename alc_traits::pointer>>;
		using packed_container_t = std::vector<T, TAlloc>;

		packed_container_t sparse;
		packed_container_t packed;


	private:
		
		/*
		* TODO: temporary solution. What is the optimal way to expand the sparse set? 
		* Or maybe it is better to use an unordered_map?
		*/
		constexpr auto try_insert(T value) -> void
		{
			if (sparse.size() <= value)
			{
				//TODO: check if n is greater than the maximum value representable by T.
				auto n = (value + 1) * 2;
				sparse.resize(n, std::numeric_limits<T>::max());
			}
			packed.emplace_back(value);
			sparse[value] = static_cast<T>(packed.size()) - 1;
		}
	};
} //namespace gargantua::ds