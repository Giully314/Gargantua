/*
* gargantua/scene/editor_system.cpp
*/

module gargantua.scene.editor_system;

import gargantua.render.render_components;
import gargantua.render.render_functions;
import gargantua.physics.physics_components;

namespace gargantua::scene
{
	auto EditorSystem::Run(ecs::ECSSystem& ecs_s) -> void
	{
		using namespace physics;
		using namespace render;
		ecs_s.ForEach<PositionComponent, RotationComponent, QuadComponent, TransformComponent>(
			[](PositionComponent& p, RotationComponent& r,
				QuadComponent& q, const TransformComponent& t)
			{
				p.p = { t.position.x, t.position.y };
				r.theta = t.rotation;
				q.size = { t.scale.x, t.scale.y };
			});

		ecs_s.ForEach<TransformComponent, TextureComponent>(render::DrawEntity::Draw);
	}

} // namespace gargantua::scene