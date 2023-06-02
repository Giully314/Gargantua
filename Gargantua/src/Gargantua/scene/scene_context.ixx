/*
* gargantua/scene/scene_context.ixx
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

export module gargantua.scene.scene_context;

import <vector>;

import gargantua.types;
import gargantua.ecs.ecs;
import gargantua.time.time_step;

namespace gargantua::scene
{
	export
	class Entity;

	export
	class SceneContext
	{
	public:

		[[nodiscard]]
		auto CreateEntity() -> Entity;


		[[nodiscard]]
		auto ECS() -> ecs::ECSSystem&
		{
			return ecs_system;
		}


		auto Startup() -> void;
		auto Shutdown() -> void;

		auto Run(const time::TimeStep& ts) -> void;
		
		auto Play() -> void
		{
			is_running = true;
		}
		
		auto Stop() -> void
		{
			is_running = false;
		}


		auto RegisterToPhysics(Entity e, f32 mass) -> void;
		auto RegisterToRenderer(Entity e) -> void;


	private:
		ecs::ECSSystem ecs_system;
		std::vector<ecs::entity_t> cameras;
		ecs::entity_t active_camera = ecs::null_entity;
		bool is_running = true;
	};
} // namespace gargantua::scene
