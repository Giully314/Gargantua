/*
* gargantua/ecs/ecs_componentmanager.ixx
*  
* PURPOSE: Manage pools of components.
* 
* CLASSES:
*	ComponentManager: Handle at runtime the storage of multiple components.
* 
* 
* DESCRIPTION:
*	Manage the ComponentStorage for the different type of components. It's important to access a component of 
*	an entity through this class because the correct idx is extracted from 
*	the id and passed to the component storage.
* 
* 
* USAGE:
*	ComponentManager mng;
*	mng.Register<Position>(); // Position must be movable.
*	
*	mng.Emplace<Position>(e1, ...); 
*	mng.Erase<Position>(e1);
* 
*	mng.Unregister<Position>();
* 
*	mng.Emplace<Position>(e1); // ERROR, Position is not registered.
* 
*	// NOTE: DO NOT use a component returned by emplace if there is another emplace in between.
*	// Memory could be reallocated and the reference would be invalid.
*	auto& p1 = mng.Emplace<Position>(e, ...);
*	auto& p2 = mng.Emplace<Position>(player, ...);
*	
*	p1.x = 42; // ERROR, could be invalid reference.
*/

export module gargantua.ecs.component_manager;

import <unordered_map>;
import <typeindex>;
import <typeinfo>;
import <concepts>;

import gargantua.types;
import gargantua.ecs.entity;
import gargantua.ecs.component_storage;
import gargantua.ecs.component_group;


namespace gargantua::ecs
{
	export class ComponentManager
	{
	public:
		explicit ComponentManager() = default;


		/*
		* Register a component type.
		* If the component is already registered do nothing.
		* Complexity: O(1).
		*/
		template <std::movable TComponent>
		auto Register() -> void
		{
			const auto i = std::type_index(typeid(TComponent));
			if (!components.contains(i)) [[likely]]
			{
				components[i] = CreateUniqueRes<ComponentStorage<TComponent>>();
			}
		}

		/*
		* Unregister a component type.
		* If the component is not registered do nothing.
		* Complexity: O(1).
		*/
		template <std::movable TComponent>
		auto Unregister() -> void
		{
			const auto i = std::type_index(typeid(TComponent));
			if (components.contains(i)) [[likely]]
			{
				components.erase(i);
			}
		}

		/*
		* Emplace a component for the entity with id.
		* Throw if the component is not registered.
		* Return the component.
		* Complexity: O(construction of component).
		*/
		template <std::movable TComponent, typename ...Args>
			requires std::constructible_from<TComponent, Args...>
		auto Emplace(const entity_t id, Args&& ...args) -> TComponent&
		{
			auto& c = GetComponentStorage<TComponent>();
			const entity_t e = EntityManipulation::Entity(id);
			return c.Emplace(e, std::forward<Args>(args)...);
		}

		/*
		* Erase the component of the entity with id.
		* Throw if the component is not registered.
		* Complexity: O(destruction of component).
		*/
		template <std::movable TComponent>
		auto Erase(const entity_t id) -> void
		{
			auto& c = GetComponentStorage<TComponent>();
			const entity_t e = EntityManipulation::Entity(id);
			c.Erase(e);
		}

		/*
		* Erase all the components associated to the id.
		*/
		auto EraseAll(const entity_t id) -> void
		{
			for (auto& [k, c] : components)
			{
				c->Erase(id);
			}
		}

		/*
		* Get the component storage of TComponent.
		* Throw if the component is not registered
		*/
		template <std::movable TComponent>
		[[nodiscard]]
		auto GetComponentStorage() -> ComponentStorage<TComponent>&
		{
			return static_cast<ComponentStorage<TComponent>&>(*components.at(std::type_index(typeid(TComponent))));
		}


		/*
		* Return a group containing the components specified.
		*/
		template <std::movable ...TComponents> 
		[[nodiscard]]
		auto Group() // -> ComponentGroup<ComponentStorage<TComponents>...>
		{
			return ComponentGroup{ GetComponentStorage<TComponents>()... };
		}

		/*
		* Get the component associated to the entity with id.
		* Throw if the entity or the component are not registered.
		* Complexity: O(1).
		*/
		template <std::movable TComponent>
		[[nodiscard]]
		auto Get(const entity_t id) -> TComponent&
		{
			const entity_t e = EntityManipulation::Entity(id);
			return GetComponentStorage<TComponent>()[e];
		}


		/*
		* Return true if the entity has the TComponent, false otherwise.
		*/
		template <std::movable TComponent>
		[[nodiscard]]
		auto Has(const entity_t id) -> bool
		{
			const entity_t e = EntityManipulation::Entity(id);
			return GetComponentStorage<TComponent>().Has(e);
		}

	private:
		std::unordered_map<std::type_index, unique_res<ComponentStorageHandler>> components;
	};

} // namespace gargantua::ecs
