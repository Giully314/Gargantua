/*
* gargantua/ecs/ecs_system.ixx
* 
* PURPOSE: glue code for the all the ecs submodules.
* 
* CLASSES:
*	ECSSystem: Handle all the ecs submodules and provide a single API for functionalities.
* 
* DESCRIPTION:
*	This module is just glue code. All the operations are directed to the right class. It's like a
*	level of indirection.
* 
* TODO:
*	- Add concepts for template parameters for better errors and preconditions.
* 
* USAGE:
*	ECSSystem ecs;
*	ecs.Register<Position>();
*	ecs.Register<Velocity>();
* 
*	auto e1 = ecs.Create();
*	ecs.Emplace<Position>(e1, ...);	
*	ecs.Emplace<Velocity>(e1, ...);	
* 
*	ecs.ForEach<Position, Velocity>([](...){...});
*	
*/

export module gargantua.ecs.ecs_system;

import <concepts>;
import <utility>;

import gargantua.types;
import gargantua.ecs.entity;
import gargantua.ecs.entity_manager;
import gargantua.ecs.component_storage;
import gargantua.ecs.component_manager;
import gargantua.ecs.component_group;


namespace gargantua::ecs
{
	export 
	class ECSSystem : public Singleton<ECSSystem>
	{
	public:
		/*
		* Get an id for an entity.
		* Complexity: O(1).
		*/
		[[nodiscard]]
		auto Create() -> entity_t
		{
			return entity_mng.Create();
		}


		/*
		* Destroy an id.
		* Precondition: the id must be alive.
		* Complexity: O(1) + O(number of components).
		*/
		auto Destroy(const entity_t id) -> void
		{
			component_mng.EraseAll(id);
			entity_mng.Destroy(id);
		}

		/*
		* Register a new component type. If already present, do nothing.
		*/
		template <std::movable TComponent> 
		auto Register() -> void
		{
			component_mng.Register<TComponent>();
		}

		/*
		* Unregister a component type. If not present, do nothing.
		*/
		template <std::movable TComponent>
		auto Unregister() -> void
		{
			component_mng.Unregister<TComponent>();
		}


		/*
		* Emplace a new component associated to id.
		* Precondition: The component type must be registered.
		* Complexity: O(1).
		*/
		template <std::movable TComponent, typename ...Args>
			requires std::constructible_from<TComponent, Args...>
		auto Emplace(entity_t id, Args&& ...args) -> TComponent&
		{
			return component_mng.Emplace<TComponent, Args...>(id, std::forward<Args>(args)...);
		}

		/*
		* Erase the component with associated id.
		* Precondition: The component type must be registered.
		* Complexity: O(1).
		*/
		template <std::movable TComponent>
		auto Erase(entity_t id) -> void
		{
			component_mng.Erase<TComponent>(id);
		}


		template <std::movable ...TComponents>
		[[nodiscard]]
		auto Group() // -> ComponentGroup<ComponentStorage<TComponents>...>
		{
			return component_mng.Group<TComponents...>();
		}


		template <std::movable TComponent>
		[[nodiscard]]
		auto Get(const entity_t id) -> TComponent&
		{
			return component_mng.Get<TComponent>(id);
		}

		template <std::movable TComponent>
		[[nodiscard]]
		auto Has(const entity_t id) -> bool
		{
			return component_mng.Has<TComponent>(id);
		}


		template <std::movable ...TComponents, typename F>
			//requires std::invocable<F, TComponents...>
		auto ForEach(F&& f) -> void
		{
			auto group = Group<TComponents...>();
			group.ForEach(std::forward<F>(f));
		}

	private:
		EntityManager entity_mng;
		ComponentManager component_mng;
	};
} // namespace gargantua::ecs

