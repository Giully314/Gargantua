/*
* gargantua/scene/scene_entity.ixx
*
* PURPOSE: Simplify the management of an entity.
*
* CLASSES:
*	Entity: id + ecs system to manage the entity using OOP.
*
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

		/*
		* Attach the component T to the entity by constructing it using Args.
		*/
		template <typename T, typename ...Args> 
			requires std::constructible_from<T, Args...>
		auto Emplace(Args&& ...args) -> T&
		{
			return context->ECS().Emplace<T, Args...>(id, std::forward<Args>(args)...);
		}


		/*
		* Erase the component T from the entity.
		*/
		template <typename T>
		auto Erase() -> void
		{
			context->ECS().Erase<T>(id);
		}

		/*
		* Get the component T.
		*/
		template <typename T>
		auto Get() -> T&
		{
			return context->ECS().Get<T>(id);
		}

		/*
		* Get the component T.
		*/
		template <typename T>
		auto Get() const -> const T&
		{
			return context->ECS().Get<T>(id);
		}


		/*
		* Check if the entity has the component T.
		*/
		template <typename T>
		auto Has() const -> bool
		{
			return context->ECS().Has<T>(id);
		}

		
		/*
		* Check if id != null_entity and id alive.
		*/
		auto IsValid() const -> bool
		{
			return id != ecs::null_entity && IsAlive();
		}


		/*
		* Check if the entity is alive.
		*/
		auto IsAlive() const -> bool
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

		/*
		* Return the entity id.
		*/
		auto ID() const noexcept -> ecs::entity_t
		{
			return id;
		}

	private:
		ecs::entity_t id{ ecs::null_entity };
		non_owned_res<SceneContext> context{ nullptr };
	};
} // namespace gargantua::scene
