/*
* gargantua/render/render2d_functions.ixx
* 
* PURPOSE: functions for ecs.
* 
* CLASSES:
*	Render2d: mix of static functions used by the ecs renderer system.
* 
*/

export module gargantua.render.functions;


import gargantua.types;
import gargantua.math;
import gargantua.physics2d.components;
import gargantua.render.components;
import gargantua.render.renderer2d_system;

export
namespace gargantua::render
{
	struct Render2d
	{
		// Update the transform component with the info from physics components.
		static auto UpdateTransformPosition(const physics2d::PositionComponent& p, TransformComponent& t) -> void
		{
			t.position = math::Vec3df{ p.p, 0.0f };
		}


		static auto UpdateTransformSize( const physics2d::QuadComponent& q, TransformComponent& t) -> void
		{
			t.scale = { q.r * 2, 0.0f };
		}


		static auto Draw(const TransformComponent& transf, const TextureComponent& t) -> void
		{
			Renderer2dSystem::Instance().DrawRotatedQuad(transf.position, transf.scale,
				transf.rotation,
				t.color, t.texture, t.tiling_factor);
		}
	};
} // namespace gargantua::render