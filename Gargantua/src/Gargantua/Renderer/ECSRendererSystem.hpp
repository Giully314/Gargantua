#pragma once
/*
Gargantua/Renderer/ECSRendererSystem.hpp

PURPOSE: rendering entities.

CLASSES:
	ECSRendererSystem: ecs system for rendering entities.

DESCRIPTION:
	This system render the entities (simple quads) and update the transform component.
	It computes the upper left corner of the quad shape using the same convention
	as the Renderer2dSystem.

*/

#include "Gargantua/Types.hpp"


#include "Gargantua/ECS/Types.hpp"
#include "Gargantua/ECS/ECSBaseSystem.hpp"
#include "Gargantua/ECS/ComponentManager.hpp"

#include "Gargantua/Renderer/ECSRendererComponents.hpp"

#include "Gargantua/Time/TimeStep.hpp"

#include "Gargantua/Systems/Renderer2dSystem.hpp"

#include "Gargantua/Physics/ECSPhysicsComponents.hpp"

#include "Gargantua/MPL/TypeList.hpp"

#include <algorithm>
#include <utility>

namespace Gargantua
{
	namespace Renderer
	{
		class ECSRendererSystem : public ECS::ECSBaseSystem
		{
		public:
			using RequiredComponents = MPL::TypeList<Physics::PositionComponent, Physics::QuadShapeComponent,
				Physics::ScaleComponent, TransformComponent, ColorComponent>;


			template <typename T>
			void Execute(const Time::TimeStep& ts, ECS::ComponentManager<T>& comp_mng)
			{
				Renderer::OrthoCameraComponent& oc = comp_mng.Get<Renderer::OrthoCameraComponent>(camera);

				r2d->BeginScene(oc.projection_view);

				std::ranges::for_each(entities_registered,
					[&](ECS::Entity e)
					{
						Physics::PositionComponent& position = comp_mng.Get<Physics::PositionComponent>(e);
						Physics::QuadShapeComponent& shape = comp_mng.Get<Physics::QuadShapeComponent>(e);
						Physics::ScaleComponent& scale = comp_mng.Get<Physics::ScaleComponent>(e);
						TransformComponent& transf = comp_mng.Get<TransformComponent>(e);
						ColorComponent& color = comp_mng.Get<ColorComponent>(e);

						//upper left corner (assume the shape is symmetric with respect to the center of mass).
						Math::Vec2df upper_left{ shape.min.x, -shape.min.y };

						transf.position = upper_left + position.position;
						transf.scale = scale.scale;
				

						r2d->DrawQuad(transf.position, transf.scale, color.color);
					}
				);

				r2d->EndScene();
			}


		
			void SetRenderer2d(SharedRes<Systems::Renderer2dSystem> r2d)
			{
				this->r2d = std::move(r2d);
			}

			void SetCamera(ECS::Entity camera)
			{
				this->camera = camera;
			}

		private:
			ECS::Entity camera;
			SharedRes<Systems::Renderer2dSystem> r2d;
		};
	} //namespace Renderer
} //namespace Gargantua