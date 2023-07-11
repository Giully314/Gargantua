/*
* gargantua/render/render_functions.ixx
*
* PURPOSE: Functions for the logic of the system for the ecs.
*
* CLASSES:
*	UpdateTransform: get info from the physics components to update the transform component.
*	DisplayEntity: Draw the entity using transform and texture components.
*/

export module gargantua.render.render_functions;

import gargantua.types;
import gargantua.math.math;
import gargantua.render.render_components;
import gargantua.physics.physics_components;
import gargantua.render.renderer2d_system;

export namespace gargantua::render
{
	struct UpdateTransform
	{
		auto operator()(const physics::PositionComponent& p, 
			const physics::QuadComponent& q,
			TransformComponent& t) -> void
		{
			t.position = math::Vec3df{ p.p, 0.0f };
			t.scale = { q.size, 0.0f };
		}
	};

	struct DisplayEntity
	{
		// TODO: Check if rotation is 0?
		auto operator()(const TransformComponent& transf, const TextureComponent& t) -> void 
		{
			Renderer2dSystem::Instance().DrawRotatedQuad(transf.position, transf.scale,
				transf.rotation, 
				t.color, t.texture, t.tiling_factor);
		}
	};

} // namespace gargantua::render
