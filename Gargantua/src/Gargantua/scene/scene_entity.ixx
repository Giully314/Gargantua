/*
* gargantua/scene/scene_entity.ixx
*
* PURPOSE: Simplify the management of an entity.
*
* CLASSES:
*	Entity: id + ecs system to manage the entity using OOP.
*
* DESCRIPTION:
*
* USAGE:
*	
*	Entity e = scene_context.CreateEntity();
*	e.Emplace<MyComponent>(...);
*	...
*	...
*	e.Destroy();
*	
*	// After destruction the entity contains the null_id.
*
*/

export module gargantua.scene.scene_entity;

import <utility>;
import <concepts>;
import <compare>;

import gargantua.types;
import gargantua.ecs.ecs;
import gargantua.scene.scene_context;


namespace gargantua::scene
{
	export
	class Entity
	{
	public:
		friend class SceneContext;

		Entity() = default;

		Entity(const ecs::entity_t id_, non_owned_res<SceneContext> context_) : id(id_),
			context(context_)
		{

		}


		auto operator==(const Entity& e) const noexcept -> bool = default;

		
		template <typename T, typename ...Args> 
			requires std::constructible_from<T, Args...>
		auto Emplace(Args&& ...args) -> T&
		{
			return context->ECS().Emplace<T, Args...>(id, std::forward<Args>(args)...);
		}

		template <typename T>
		auto Erase() -> void
		{
			context->ECS().Erase<T>(id);
		}

		template <typename T>
		auto Get() -> T&
		{
			return context->ECS().Get<T>(id);
		}

		template <typename T>
		auto Has() -> bool
		{
			return context->ECS().Has<T>(id);
		}

		
		/*
		* Check if id != null_entity and id alive.
		*/
		auto IsValid() -> bool
		{
			return id != ecs::null_entity && IsAlive();
		}


		/*
		* Check if the entity is alive.
		*/
		auto IsAlive() -> bool
		{
			return context->ECS().IsAlive(id);
		}


		/*
		* If the entity is valid, destroy the id and set it to null.
		*/
		auto Destroy() -> void
		{
			if (IsValid())
			{
				context->DestroyEntity(id);
				id = ecs::null_entity;
			}
		}


		auto ID() const noexcept -> ecs::entity_t
		{
			return id;
		}

	private:
		ecs::entity_t id{ ecs::null_entity };
		non_owned_res<SceneContext> context{ nullptr };
	};
} // namespace gargantua::scene
