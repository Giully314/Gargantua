/*
* gargantua/render/render_renderecssystem.ixx
*
* PURPOSE: Provide management for rendering using ecs.
*
* CLASSES:
*	RendererSystem: singleton that render all the entities that have TransformComponent and TextureComponent.
*/

export module gargantua.render.render_ecs_system;

import gargantua.types;
import gargantua.render.ecs_components;
import gargantua.render.ecs_functions;
import gargantua.ecs;
import gargantua.time.time_step;

namespace gargantua::render
{
	export class RenderECSSystem : private NonCopyable, NonMovable
	{
	public:
		[[nodiscard]]
		static auto Instance() -> RenderECSSystem&
		{
			static RenderECSSystem sys;
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
		auto Register(const ecs::entity_t e, ecs::ECSSystem& ecs_s) -> void
		{
			ecs_s.Emplace<TransformComponent>(e);
			ecs_s.Emplace<TextureComponent>(e);
		}


		/*
		* Remove TransformComponent, TextureComponent from the entity.
		*/
		auto Unregister(const ecs::entity_t e, ecs::ECSSystem& ecs_s) -> void
		{
			ecs_s.Erase<TransformComponent>(e);
			ecs_s.Erase<TextureComponent>(e);
		}


		/*
		* Run rendering on every entity that has a TransformComponent and Texture Component.
		*/
		auto Run(const time::TimeStep& ts, ecs::ECSSystem& ecs_s) -> void
		{
			ecs_s.ForEach<TransformComponent, TextureComponent>(RenderECS::Draw);
		}

	private:
		RenderECSSystem() = default;
	};
} // namespace gargantua::render