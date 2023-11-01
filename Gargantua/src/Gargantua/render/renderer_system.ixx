/*
* gargantua/render/renderer_system.ixx
*
* PURPOSE: run the ecs rendering system.
*
* CLASSES:
*	RendererSystem: render all the entities that have TransformComponent and TextureComponent.
* 
*/

export module gargantua.render.renderer_system;

import gargantua.types;
import gargantua.render.components;
import gargantua.render.functions;
import gargantua.ecs;
import gargantua.time.time_step;
import gargantua.physics2d.components;

namespace gargantua::render
{
	export
	class RendererSystem : private NonCopyable, NonMovable
	{
	public:
		[[nodiscard]]
		static
		auto Instance() -> RendererSystem&
		{
			static RendererSystem sys;
			return sys;
		}


		/*
		* Register all the render components.
		*/
		auto Startup(ecs::ECSSystem& ecs_s)
		{
			ecs_s.Register<TransformComponent>();
			ecs_s.Register<TextureComponent>();
		}


		/*
		* Attach TransformComponent, TextureComponent to the entity.
		*/
		auto Register(ecs::entity_t e,
			ecs::ECSSystem& ecs_s) -> void
		{
			ecs_s.Emplace<TransformComponent>(e);
			ecs_s.Emplace<TextureComponent>(e);
		}


		/*
		* Remove TransformComponent, TextureComponent from the entity.
		*/
		auto Unregister(ecs::entity_t e, ecs::ECSSystem& ecs_s) -> void
		{
			ecs_s.Erase<TransformComponent>(e);
			ecs_s.Erase<TextureComponent>(e);
		}


		/*
		* Run rendering.
		*/
		auto Run(const time::TimeStep& ts, ecs::ECSSystem& ecs_s) -> void
		{
			using namespace physics2d;
			ecs_s.ForEach<PositionComponent,TransformComponent>(Render2d::UpdateTransformPosition);
			ecs_s.ForEach<QuadComponent,TransformComponent>(Render2d::UpdateTransformSize);
			ecs_s.ForEach<TransformComponent, TextureComponent>(Render2d::Draw);
		}	

	private:
		RendererSystem() = default;
	};

} // namespace gargantua::render

