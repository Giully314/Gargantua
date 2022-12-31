/*
gargantua/ecs/component_storage.ixx

PURPOSE:

CLASSES:

DESCRIPTION:

USAGE:

*/

export module gargantua.ecs.ecs:component_storage;

import <concepts>;
import <vector>;
import <utility>;
import <memory>;


import :entity;
import gargantua.types;
import gargantua.datastructures.sparse_set;


export namespace gargantua::ecs
{
	//https://developercommunity.visualstudio.com/t/C-20-module-problem-on-pure-virtual-an/1441612
	//This should be virtual pure destructor, but after 18 months, visual studio developers couldn't fix this. Good job.
	class ComponentStorageHandler
	{
	public:
		virtual ~ComponentStorageHandler() = default;
	};


	/*
	* TComponent: type of the component
	* TAlloc: allocator used by std::vector for the TComponent
	*/
	template <std::semiregular TComponent, typename TAllocComp = std::allocator<TComponent>, 
		typename TAllocSet = std::allocator<entity_t>>
	class ComponentStorage : public ComponentStorageHandler
	{
	public:	
		using iterator = std::vector<TComponent, TAllocComp>::iterator;
		using const_iterator = std::vector<TComponent, TAllocComp>::const_iterator;


		/*
		* 
		* Emplace a component for the entity e.
		* If the entity is already in the container the behavior is undefined.
		* Complexity: O(construction of component). For simple types is O(1).
		*/

		template <typename ...Args>
			requires std::constructible_from<TComponent, Args...> 
		[[nodiscard]]
		auto Emplace(entity_t e, Args&& ...args) -> TComponent&
		{
			auto id = EntityManipulation::ExtractID(e);
			entities_registered.insert(id);
			components.emplace_back(std::forward<Args>(args)...);
			return components.back();
		}


		/*
		* Erase the component associated to entity e.
		* If the entity has no component the behavior is undefined.
		* Complexity: O(1).
		*/
		auto Erase(entity_t e) -> void
		{
			using std::swap;
			auto id = EntityManipulation::ExtractID(e);
			auto idx = entities_registered.index_of(id);
			entities_registered.erase(id);
			swap(components[idx], components.back());
			components.pop_back();
		}

		//temp function for test
		[[nodiscard]]
		auto IndexOf(entity_t e) -> natural_t
		{
			/*
			* Note on cast: i know that the id is less than 32 bit so there at most 2^32 idxs.
			*/
			auto id = EntityManipulation::ExtractID(e);
			return static_cast<natural_t>(entities_registered.index_of(id));
		}


		/*
		* Check if a entity has a component.
		* Complexity: O(1).
		*/
		[[nodiscard]]
		auto Contains(entity_t e) -> bool
		{
			auto id = EntityManipulation::ExtractID(e);
			return entities_registered.contains(id);
		}


		[[nodiscard]]
		auto Size() const noexcept -> natural_t
		{
			return components.size();
		}


		/*
		* Access the component of entity e.
		* If the entity has not the component, the behavior is undefined.
		* Complexity: O(1).
		*/
		[[nodiscard]]
		auto operator[](entity_t e) -> TComponent&
		{
			auto id = EntityManipulation::ExtractID(e);
			return components[entities_registered.index_of(id)];
		}


		/*
		* Get the sparse set that contains all the entities that have the component.
		*/
		[[nodiscard]]
		auto GetEntities() const noexcept -> const datastructures::SparseSet<entity_t>&
		{
			return entities_registered;
		}


		//******************** ITERATORS FOR COMPONENTS ***********************
		
		/*
		* Begin iterator for the vector of components.
		*/
		[[nodiscard]]
		auto begin() noexcept -> iterator
		{
			return components.begin();
		}

		/*
		* End iterator for the vector of components.
		*/
		[[nodiscard]]
		auto end() noexcept -> iterator
		{
			return components.end();
		}


		/*
		* Constant begin iterator for the vector of components.
		*/
		[[nodiscard]]
		auto cbegin() const noexcept -> const_iterator
		{
			return components.cbegin();
		}

		/*
		* Constant end iterator for the vector of components.
		*/
		[[nodiscard]]
		auto cend() const noexcept -> const_iterator
		{
			return components.cend();
		}
		
		
		//******************** ITERATORS FOR COMPONENTS ***********************


	private:
		//Note that the packed array and the components array are in sync.
		//packed[0] is the entity that has the component in components[0].
		datastructures::SparseSet<entity_t, TAllocSet> entities_registered;
		std::vector<TComponent, TAllocComp> components;
	};

} //namespace gargantua::ecs