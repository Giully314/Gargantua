/*
* gargantua/render/render_functions.ixx
*
* PURPOSE: Functions for iterate ECS components.
*
* CLASSES:
*
* DESCRIPTION:
*
* USAGE:
*
*/

export module gargantua.render.render_functions;

import gargantua.types;
import gargantua.render.render_components;
import gargantua.physics.physics_components;
import gargantua.render.renderer2d_system;

export namespace gargantua::render
{
	struct UpdateTransform
	{
		auto operator()(const physics::PositionComponent& p, TransformComponent& t) -> void
		{
			t.position = p.p;
		}
	};

	struct DisplayEntity
	{
		// TODO: Check if rotation is 0?
		auto operator()(const TransformComponent& transf, const TextureComponent& t) -> void 
		{
			Renderer2dSystem::Instance().DrawRotatedQuad(transf.position, transf.scale,
				transf.rotation, t.texture);
		}
	};

} // namespace gargantua::render
