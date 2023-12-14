/*
* gargantua/render/render_ecsfunctions.ixx
* 
* PURPOSE: provide functions for ecs.
* 
* CLASSES:
*	Render2d: mix of static functions used by the ecs renderer system.
*/

export module gargantua.render.ecs_functions;


import gargantua.types;
import gargantua.math;
import gargantua.render.ecs_components;
import gargantua.render.renderer_system;

namespace gargantua::render
{
	export struct RenderECS
	{
		static auto Draw(const TransformComponent& transf, const TextureComponent& t) -> void
		{
			RendererSystem::Instance().DrawRotatedQuad(transf.position, transf.scale,
				transf.rotation,
		 		t.color, t.texture, t.tiling_factor);
		}
	};
} // namespace gargantua::render