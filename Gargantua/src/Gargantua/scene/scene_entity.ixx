/*
* gargantua/scene/scene_entity.ixx
*
* PURPOSE:
*
* CLASSES:
*
* DESCRIPTION:
*
* USAGE:
*
*/

export module gargantua.scene.scene_entity;

import <utility>;

import gargantua.types;
import gargantua.ecs.ecs;
import gargantua.scene.scene_context;


namespace gargantua::scene
{
	export
	class Entity
	{
	public:
		Entity() : Entity(ecs::null_entity, nullptr)
		{

		}

		Entity(const ecs::entity_t id_, non_owned_res<SceneContext> context_) : id(id_),
			context(context_)
		{

		}

		
		template <typename T, typename ...Args> 
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

	public:
		ecs::entity_t id;

	private:
		non_owned_res<SceneContext> context;
	};
} // namespace gargantua::scene
