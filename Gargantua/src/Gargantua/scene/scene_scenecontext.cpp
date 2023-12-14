/*
* gargantua/scene/scene_context.cpp
*/

module;

#include <gargantua/log/logger_macro.hpp>

module gargantua.scene.scene_context;

import gargantua.ecs;
import gargantua.scene.scene_entity;
import gargantua.scene.editor_system;
import gargantua.physics;
import gargantua.render;
import gargantua.log;
import gargantua.scene.ecs_components;
import gargantua.math.vector;

namespace gargantua::scene
{
	auto SceneContext::CreateEntity() -> Entity
	{
		const auto id = ecs_system.Create();
		entities.push_back(id);
		return Entity{ id, this };
	}


	auto SceneContext::CreateEntity(const std::string_view name) -> Entity
	{
		auto e = CreateEntity();
		e.Emplace<TagComponent>(name);
		return e;
	}


	auto SceneContext::DestroyEntity(Entity e) -> void
	{
		DestroyEntity(e.id);
	}
		

	auto SceneContext::DestroyEntity(ecs::entity_t e) -> void
	{
		//Temporary, slow.
		std::erase(entities, e);
		ecs_system.Destroy(e);
	}


	auto SceneContext::Startup() -> void
	{
		physics::PhysicsECSSystem::Instance().Startup(ecs_system);
		render::RenderECSSystem::Instance().Startup(ecs_system);
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
		if (mode == SceneMode::Editor)
		{
			EditorSystem::Instance().Run(ecs_system);
		}
		else
		{
			using namespace physics;
			using namespace render;

			PhysicsECSSystem::Instance().Run(ts, ecs_system);

			// Update the transform component position with the info from physics position.
			ecs_system.ForEach<PositionComponent, TransformComponent>(
				[](const PositionComponent& p, TransformComponent& t) -> void
				{
					t.position.x = p.p.x;
					t.position.y = p.p.y;
				});

			// Update the transform component size with the info from physics size.
			ecs_system.ForEach<QuadComponent, TransformComponent>(
				[](const QuadComponent& q, TransformComponent& t) -> void
				{
					t.scale.x = q.r.x * 2.0f;
					t.scale.y = q.r.y * 2.0f;
				});

			render::RenderECSSystem::Instance().Run(ts, ecs_system);
		}
	}


	auto SceneContext::RegisterToPhysics(const Entity e, const f32 mass, const math::Vec2df& size) -> void
	{
		physics::PhysicsECSSystem::Instance().Register(e.id, mass, size, ecs_system);
	}


	auto SceneContext::RegisterToRenderer(Entity e) -> void
	{
		render::RenderECSSystem::Instance().Register(e.id, ecs_system);
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
		/*GRG_CORE_DEBUG("Scene distance{}\n{}", camera.camera.GetDistance(), 
			camera.GetProjection().ToString());*/

		return camera.Projection() * transf.Transform().Inverse();
	}

} // namespace gargantua::scene
