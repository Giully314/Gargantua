/*
* gargantua/ecs/ecs_componentstorage.ixx
* 
* PURPOSE: Manage the storage for a component.
* 
* CLASSES:
*	ComponentStorage: Handle the storage for the component and the sparse set associated.
* 
* DESCRIPTION:
*	This class manages the synchronization between the vector of component and the sparse set used to keep info
*	about the entities registered. 
* 
* 
* USAGE:
*	ComponentStorage<Position> s;
* 
*	// assume entity e1 have been created by EntityManager.
* 
*	// Note that we need to extract the entity to access the component storage. This is done by the ComponentManager once
*	// to avoid repetition of extraction in case of accessing multiple component storages with the same entity.
*	auto idx1 = EntityManipulation::Entity(e1);
*	s.Emplace(idx1);
*/

export module gargantua.ecs.component_storage;

import <vector>;
import <utility>;
import <concepts>;

import gargantua.types;
import gargantua.ecs.entity;
import gargantua.ds.sparse_set;


namespace gargantua::ecs
{
	export class ComponentStorageHandler : private NonCopyable
	{
	public:
		virtual ~ComponentStorageHandler() = default;

		virtual auto Erase(entity_t e) -> void = 0;
	};


	export template <typename T>
		requires std::default_initializable<T> && std::movable<T>
	class ComponentStorage : public ComponentStorageHandler
	{
	public:
		//friend class ComponentGroup;
		using value_type = T;

		constexpr explicit ComponentStorage() = default;


		/*
		* Emplace a component for the entity e and return it.
		* Precondition: e must be a valid entity.
		* Complexity: O(construction of component). For simple types is O(1).
		*/
		template <typename ...Args>
			requires std::constructible_from<T, Args...>
		constexpr auto Emplace(const entity_t e, Args&& ...args) -> T&
		{
			if (entities_registered.contains(e)) [[unlikely]]
			{
				auto idx = entities_registered.index_of(e);
				return components[idx];
			}
			entities_registered.insert(e);
			components.emplace_back(std::forward<Args>(args)...);
			return components.back();
		}


		/*
		* Erase the component associated to entity e.
		* If the entity is not registered does nothing.
		* Precondition: e must be a valid entity.
		* Complexity: O(1).
		*/
		constexpr auto Erase(const entity_t e) -> void override
		{
			if (!entities_registered.contains(e)) [[unlikely]]
			{
				return;
			}

			using std::swap;
			auto idx = entities_registered.index_of(e);
			entities_registered.erase(e);
			swap(components[idx], components.back());
			components.pop_back();
		}

		/*
		* Return the number of components.
		*/
		[[nodiscard]]
		constexpr auto Size() const noexcept -> u32
		{
			return static_cast<u32>(components.size());
		}


		/*
		* Return if the entity has the component.
		* Complexity: O(1).
		*/
		[[nodiscard]]
		constexpr auto Has(const entity_t e) const noexcept -> bool
		{
			return entities_registered.contains(e);
		}
		
		// TODO: memory access to retrieve the idx of the entity in the packed array could be too slow.
		/*
		* Return the component associated to entity e.
		* Precondition: e must be a valid entity registered.
		* Complexity: O(1).
		*/
		[[nodiscard]]
		constexpr auto operator[](const entity_t e) -> T&
		{
			return components[entities_registered.index_of(e)];
		}

		//****************** ITERATORS *******************************
		
		// Return the begin iterator of the packed array in the sparse set.
		[[nodiscard]]
		constexpr auto begin() noexcept -> ds::SparseSet<entity_t>::iterator
		{
			return entities_registered.begin();
		}

		// Return the end iterator of the packed array in the sparse set.
		[[nodiscard]]
		constexpr auto end() noexcept -> ds::SparseSet<entity_t>::iterator
		{
			return entities_registered.end();
		}


		// Return the const begin iterator of the packed array in the sparse set.
		[[nodiscard]]
		constexpr auto begin() const noexcept -> ds::SparseSet<entity_t>::const_iterator
		{
			return entities_registered.begin();
		}

		// Return the const end iterator of the packed array in the sparse set.
		[[nodiscard]]
		constexpr auto end() const noexcept -> ds::SparseSet<entity_t>::const_iterator
		{
			return entities_registered.end();
		}


		// Return the const begin iterator of the packed array in the sparse set.
		[[nodiscard]]
		constexpr auto cbegin() const noexcept -> ds::SparseSet<entity_t>::const_iterator
		{
			return entities_registered.begin();
		}

		// Return the const end iterator of the packed array in the sparse set.
		[[nodiscard]]
		constexpr auto cend() const noexcept -> ds::SparseSet<entity_t>::const_iterator
		{
			return entities_registered.end();
		}

		//****************** ITERATORS *******************************


	private:
		ds::SparseSet<entity_t> entities_registered;
		std::vector<T> components;
	};
} // namespace gargantua::ecs
