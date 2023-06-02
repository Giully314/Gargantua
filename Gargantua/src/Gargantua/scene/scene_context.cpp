/*
* gargantua/scene/scene_context.cpp
*/

module gargantua.scene.scene_context;

import gargantua.ecs.ecs;
import gargantua.scene.scene_entity;
import gargantua.physics.physics;
import gargantua.render.render;


namespace gargantua::scene
{
	auto SceneContext::CreateEntity() -> Entity
	{
		const auto id = ecs_system.Create();
		return Entity{ id, this };
	}

	auto SceneContext::Startup() -> void
	{
		physics::PhysicsSystem::Instance().Startup(ecs_system);
		render::RendererSystem::Instance().Startup(ecs_system);
	}

	auto SceneContext::Shutdown() -> void
	{

	}

	auto SceneContext::Run(const time::TimeStep& ts) -> void
	{
		if (!is_running)
		{
			return;
		}

		physics::PhysicsSystem::Instance().Run(ts, ecs_system);
		render::RendererSystem::Instance().Run(ts, ecs_system);
	}



	auto SceneContext::RegisterToPhysics(Entity e, f32 mass) -> void
	{
		physics::PhysicsSystem::Instance().Register(e.id, mass, ecs_system);
	}


	auto SceneContext::RegisterToRenderer(Entity e) -> void
	{
		render::RendererSystem::Instance().Register(e.id, ecs_system);
	}

} // namespace gargantua::scene
