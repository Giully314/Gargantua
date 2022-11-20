/*
gargantua/ecs/component_storage.ixx

PURPOSE:

CLASSES:

DESCRIPTION:

USAGE:

*/

export module gargantua.ecs.component_storage;

import <concepts>;
import <vector>;
import <unordered_map>;
import <utility>;
import <memory>;

import gargantua.ecs.ecs_types;


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
	template <std::semiregular TComponent, typename TAlloc = std::allocator<TComponent>>
	class ComponentStorage : public ComponentStorageHandler
	{
	public:
		using ComponentType = TComponent;
		using AllocatorType = TAlloc;


		/*
		* Emplace a component associated to an entity id and return it.
		* If the entity already has a component, return the component.
		* 
		* Complexity: O(1). (Depends only on the complexity of construction of the component)
		*/
		template <typename ...Args>
			requires std::constructible_from<ComponentType, Args...>
		auto Emplace(entity_t e, Args&& ...args) -> ComponentType&
		{
			if (Contains(e)) [[unlikely]]
			{
				return components[sparse[e]];
			}

			
			auto idx = packed.size();
			sparse[idx] = 
		}


		/*
		* Erase a component associated to the entity e.
		* If the component is not present, return false.
		* The order of components is not maintained because to allow fast erase, the component to be erased is swapped
		* with the last component and popped back.
		* 
		* Complexity: O(1). 
		*/
		auto Erase(entity_t e) -> void  
		{
				
		}



		/*
		
		*/
		[[nodiscard]]
		auto operator[](entity_t e) -> ComponentType&
		{
			
		}


		[[nodiscard]]
		auto Size() const noexcept -> std::vector<entity_t>::size_type
		{
			return packed.size();
		}


		[[nodiscard]]
		auto Contains(entity_t e) const noexcept -> bool
		{
			return packed[sparse[e]] == e;
		}


		//*********** ITERATORS ********************************
		
		[[nodiscard]]
		auto begin() noexcept -> std::vector<entity_t>::iterator
		{
			return packed.begin();
		}

		[[nodiscard]]
		auto end() noexcept -> std::vector<entity_t>::iterator
		{
			return packed.end();
		}


		[[nodiscard]]
		auto cbegin() const noexcept -> std::vector<entity_t>::const_iterator
		{
			return packed.cbegin();
		}

		[[nodiscard]]
		auto cend() const noexcept -> std::vector<entity_t>::const_iterator
		{
			return packed.cend();
		}


		//*********** ITERATORS ********************************


	private:
		std::unordered_map<entity_t, natural_t> sparse;

		//packed and components are in sync. 
		std::vector<entity_t> packed; //entities
		std::vector <T, TAlloc> components;
	};

} //namespace gargantua::ecs