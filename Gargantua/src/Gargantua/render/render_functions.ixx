/*
* gargantua/render/render_functions.ixx
*
* PURPOSE: Functions for the logic of the system for the ecs.
*
* CLASSES:
*	UpdateTransform: get info from the physics components to update the transform component.
*	DisplayEntity: Draw the entity using transform and texture components.
* 
* 
* TODO: 
*	- i don't like the fact the we need to create an object UpdateTransform to call
*	the operator(). Because we don't need to store any information, just use a static function.
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
			const physics::RotationComponent& r,
			const physics::QuadComponent& q,
			TransformComponent& t) -> void
		{
			t.position = math::Vec3df{ p.p, 0.0f };
			t.scale = { q.size, 0.0f };
			t.rotation = r.theta;
		}
	};

	struct DrawEntity
	{
		// TODO: Check if rotation is 0?
		static 
		auto Draw(const TransformComponent& transf, const TextureComponent& t) -> void 
		{
			Renderer2dSystem::Instance().DrawRotatedQuad(transf.position, transf.scale,
				transf.rotation, 
				t.color, t.texture, t.tiling_factor);
		}
	};

} // namespace gargantua::render
