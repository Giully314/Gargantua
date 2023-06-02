	/*
	* gargantua/render/renderer_system.ixx
	*
	* PURPOSE: System for ECS components.
	*
	* CLASSES:
	* 
	* DESCRIPTION:
	*
	* USAGE:
	*
	*/

export module gargantua.render.renderer_system;

import gargantua.types;
import gargantua.render.render_components;
import gargantua.render.render_functions;
import gargantua.ecs.ecs;
import gargantua.time.time_step;

namespace gargantua::render
{
	export
	class RendererSystem : public Singleton<RendererSystem>
	{
	public:

		/*
		* Register all the render components.
		*/
		auto Startup(ecs::ECSSystem& ecs_s = ecs::ECSSystem::Instance())
		{
			ecs_s.Register<TransformComponent>();
			ecs_s.Register<TextureComponent>();
		}


		/*
		* Attach TransformComponent, TextureComponent to the entity.
		*/
		auto Register(ecs::entity_t e,
			ecs::ECSSystem& ecs_s = ecs::ECSSystem::Instance()) -> void
		{
			ecs_s.Emplace<TransformComponent>(e);
			ecs_s.Emplace<TextureComponent>(e);
		}


		/*
		* Remove TransformComponent, TextureComponent from the entity.
		*/
		auto Unregister(ecs::entity_t e, ecs::ECSSystem& ecs_s = ecs::ECSSystem::Instance()) -> void
		{
			ecs_s.Erase<TransformComponent>(e);
			ecs_s.Erase<TextureComponent>(e);
		}


		/*
		* Run phisycs simulation.
		*/
		auto Run(const time::TimeStep& ts, ecs::ECSSystem& ecs_s = ecs::ECSSystem::Instance()) -> void
		{
			UpdateTransform upt;
			DisplayEntity draw;
			ecs_s.ForEach<physics::PositionComponent, TransformComponent>(upt);
			ecs_s.ForEach<TransformComponent, TextureComponent>(draw);
		}	
	};

} // namespace gargantua::render

