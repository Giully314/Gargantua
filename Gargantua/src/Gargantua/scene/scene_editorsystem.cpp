/*
* gargantua/scene/scene_editorsystem.cpp
*/

module gargantua.scene.editor_system;

import gargantua.render.ecs_components;
import gargantua.render.ecs_functions;
import gargantua.physics.ecs_components;

namespace gargantua::scene
{
	auto EditorSystem::Run(ecs::ECSSystem& ecs_s) -> void
	{
		using namespace physics;
		using namespace render;
		ecs_s.ForEach<PositionComponent, QuadComponent, TransformComponent>(
			[](PositionComponent& p, QuadComponent& q, const TransformComponent& t)
			{
				p.p = math::Vec2df{ t.position.x, t.position.y };
				q.r = math::Vec2df{ t.scale.x / 2.0f, t.scale.y / 2.0f };
			});

		ecs_s.ForEach<TransformComponent, TextureComponent>(render::RenderECS::Draw);
	}

} // namespace gargantua::scene