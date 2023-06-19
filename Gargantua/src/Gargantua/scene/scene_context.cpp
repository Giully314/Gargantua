/*
* gargantua/scene/scene_context.cpp
*/

module;

#include <gargantua/log/logger_macro.hpp>

module gargantua.scene.scene_context;

import gargantua.ecs.ecs;
import gargantua.scene.scene_entity;
import gargantua.physics.physics;
import gargantua.render.render;
import gargantua.log.log;
import gargantua.scene.scene_components;

namespace gargantua::scene
{
	auto SceneContext::CreateEntity() -> Entity
	{
		const auto id = ecs_system.Create();
		entities.push_back(id);
		return Entity{ id, this };
	}

	auto SceneContext::CreateEntityFromID(const ecs::entity_t e) -> Entity
	{
		return Entity{ e, this };
	}


	auto SceneContext::DeleteEntity(Entity e) -> void
	{
		DeleteEntity(e.id);
	}


	auto SceneContext::DeleteEntity(ecs::entity_t e) -> void
	{
		//Temporary, slow.
		std::erase(entities, e);
	}


	auto SceneContext::Startup() -> void
	{
		physics::PhysicsSystem::Instance().Startup(ecs_system);
		render::RendererSystem::Instance().Startup(ecs_system);
		ecs_system.Register<render::CameraComponent>();
		ecs_system.Register<TagComponent>();

		CreateCamera("Editor");
		SetActiveCamera("Editor");
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

	auto SceneContext::SetViewport(u32 width, u32 height) -> void
	{
		viewport_width = width;
		viewport_height = height;

		auto g = ecs_system.Group<render::CameraComponent>();
		g.ForEach([=](auto& c)
			{
				c.camera.SetViewport(width, height);
			});
	}


	auto SceneContext::GetActiveCamera() -> Entity
	{
		return Entity{ active_camera, this };
	}


	auto SceneContext::GetActiveCameraMatrix() -> math::Mat4df
	{
		auto& transf = ecs_system.Get<render::TransformComponent>(active_camera);
		auto& camera = ecs_system.Get<render::CameraComponent>(active_camera);
		GRG_CORE_DEBUG("Scene distance{}\n{}", camera.camera.GetDistance(), 
			camera.GetProjection().ToString());

		return camera.GetProjection() * transf.Transform().Inverse();
	}

} // namespace gargantua::scene
