/*
* gargantua/scene/editor_system.cpp
*/

module gargantua.scene.editor_system;

import gargantua.render.components;
import gargantua.render.functions;
import gargantua.physics2d.components;

namespace gargantua::scene
{
	auto EditorSystem::Run(ecs::ECSSystem& ecs_s) -> void
	{
		using namespace physics2d;
		using namespace render;
		ecs_s.ForEach<PositionComponent, QuadComponent, TransformComponent>(
			[](PositionComponent& p, QuadComponent& q, const TransformComponent& t)
			{
				p.p = { t.position.x, t.position.y };
				q.r = { t.scale.x / 2.0f, t.scale.y / 2.0f };
			});

		ecs_s.ForEach<TransformComponent, TextureComponent>(render::Render2d::Draw);
	}

} // namespace gargantua::scene