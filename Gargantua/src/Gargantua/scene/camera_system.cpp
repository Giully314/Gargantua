/*
* gargantua/scene/camera_system.cpp
*/

module gargantua.scene.camera_system;

import gargantua.render;

namespace gargantua::scene
{
	auto CameraSystem::Create(const std::string& name, u32 viewport_width, u32 viewport_height) -> ecs::entity_t
	{
		ecs::entity_t camera = ecs_system->Create();
		ecs_system->Emplace<render::TransformComponent>(camera);
		auto& c = ecs_system->Emplace<render::CameraComponent>(camera);
		c.camera.SetViewport(viewport_width, viewport_height);
		ecs_system->Emplace<TagComponent>(camera, name);
		cameras.push_back(camera);
		return camera;
	}


	auto CameraSystem::Destroy(const std::string& name) -> void
	{
		auto g = ecs_system->Group<TagComponent, render::CameraComponent>();
		auto v = g.View();
		ecs::entity_t entity = ecs::null_entity;

		for (auto e : v)
		{
			auto& tag = ecs_system->Get<TagComponent>(e);
			if (tag.name == name)
			{
				entity = e;
				break;
			}
		}

		if (entity != ecs::null_entity)
		{
			std::erase(cameras, entity);
			ecs_system->Destroy(entity);
		}
	}


	auto CameraSystem::Get(const std::string& name) -> ecs::entity_t
	{
		auto g = ecs_system->Group<TagComponent, render::CameraComponent>();
		auto v = g.View();
		for (auto e : v)
		{
			auto& tag = ecs_system->Get<TagComponent>(e);
			if (tag.name == name)
			{
				return e;
			}
		}
		return ecs::null_entity;
	}

} // namespace gargantua::scene
