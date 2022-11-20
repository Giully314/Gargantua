/*
gargantua/datastructures/sparse_set.ixx

PURPOSE: sparse set.

CLASSES: 
	SparseSet: sparse set with double sparse map.

DESCRIPTION:
	This implementation uses 2 maps to keep track of index in both directions, from sparse to packed and from
	packed to sparse. This allows to both inserting and removing O(1).
	Traverse the packed array is fast because the memory is contigous.
	Access a single data can be problematic in terms of cache hits because there is the level of indirection
	from the sparse map.

USAGE:
	SparseSet<int, PositionComponent> s;
	s.Emplace(2, x, y);
	
	//Fast iteration for all the packed data.
	for (auto& p : s)
	{
		...
	}
	
	s.Remove(2);
*/

export module gargantua.datastructures.sparse_set;

import <concepts>;
import <vector>;
import <unordered_map>;

import gargantua.types;

export namespace gargantua::datastructures
{
	template <std::regular TIndex, std::semiregular TData>
	class SparseSet
	{
	public:
		/*
		* Emplace a data associated to an idx and return it.
		* If the idx already has a data, return the data.
		*
		* Complexity: O(1). (Depends only on the complexity of construction of the component)
		*/
		template <typename ...Args> 
			requires std::constructible_from<TData, Args...>
		auto Emplace(TIndex idx, Args&& ...args) -> TData&
		{
			//The idx is already registered so return the data associated.
			if (auto it = sparse_to_packed.find(idx); it != sparse_to_packed.end()) [[unlikely]]
			{
				return packed[it->second];
			}

			//Emplace a new element.
			packed.emplace_back(std::forward<Args>(args)...);
			auto i = static_cast<natural_t>(packed.size() - 1);

			sparse_to_packed[idx] = i;
			packed_to_sparse[i] = idx;

			return packed.back();
		}

		/*
		* Erase a data associated to the index idx.
		* If the data is not present, return false.
		* Note that after calling this function, all the references are invalidated.
		*
		* Complexity: O(1).
		*/
		auto Erase(TIndex idx) -> bool
		{
			auto it_idx_to_data = sparse_to_packed.find(idx);

			//The idx has no data.
			if (it_idx_to_data == sparse_to_packed.end()) [[unlikely]]
			{
				return false;
			}

			//If there is only one component, just pop_back.
			if (packed.size() == 1) [[unlikely]]
			{
				packed.pop_back();
				sparse_to_packed.clear();
				packed_to_sparse.clear();
				return true;
			}


			//Retrieve info about the 2 components that must be swapped

			auto it_data_to_idx = packed_to_sparse.find(it_idx_to_data->second);

			auto node_last_component = packed_to_sparse.extract(static_cast<natural_t>(packed.size() - 1));
			auto node_last_idx = sparse_to_packed.extract(node_last_component.mapped());

			std::swap(packed[it_idx_to_data->second], packed[node_last_idx.mapped()]);
			packed.pop_back();

			//Update the info

			node_last_component.key() = it_idx_to_data->second;
			node_last_idx.mapped() = it_idx_to_data->second;

			packed_to_sparse.erase(it_idx_to_data->second);
			sparse_to_packed.erase(it_idx_to_data);

			sparse_to_packed.insert(std::move(node_last_idx));
			packed_to_sparse.insert(std::move(node_last_component));

			return true;
		}

		/*
		* Return the data associated to idx. If idx is not present, throw out_of_range.
		* Complexity: O(1).
		*/
		auto operator[](TIndex idx) -> TData&
		{
			return packed[sparse_to_packed.at(idx)];
		}

		/*
		* Return the data associated to idx. If idx is not present, throw out_of_range.
		* Complexity: O(1).
		*/
		auto operator[](TIndex idx) const -> const TData&
		{
			return packed[sparse_to_packed.at(idx)];
		}



		//********************* ITERATORS FOR PACKED *************************************
		
		auto begin() noexcept -> std::vector<TData>::iterator
		{
			return packed.begin();
		}

		auto end() noexcept -> std::vector<TData>::iterator
		{
			return packed.end();
		}


		auto cbegin() const noexcept -> std::vector<TData>::const_iterator
		{
			return packed.cbegin();
		}

		auto cend() const noexcept -> std::vector<TData>::const_iterator
		{
			return packed.cend();
		}
		
		//********************* ITERATORS FOR PACKED *************************************
		
		


	private:
		std::unordered_map<TIndex, natural_t> sparse;
		std::vector<TIndex> packed;
		std::vector<TData> data;
	};
} //namespace gargantua::datastructures