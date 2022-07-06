#pragma once
/*
Gargantua/Renderer/ECSCameraSystem.hpp

PURPOSE: Manage cameras.

CLASSES:
	ECSCameraSystem: ecs system for updating cameras.

DESCRIPTION:
	Update the projection_view matrix of every camera registered. 
	Cameras could have the input compnent that specify a movement or a rotation; if so
	update the respective values. Note that usually i don't like to check if an entity
	has a component, but in this case the number of entities should be really small
	and this check is just insignificant.
*/

#include "Gargantua/ECS/Types.hpp"
#include "Gargantua/ECS/ECSBaseSystem.hpp"
#include "Gargantua/ECS/ComponentManager.hpp"

#include "Gargantua/Math/MathFunctions.hpp"
#include "Gargantua/Math/Mat4d.hpp"
#include "Gargantua/Math/Vec3d.hpp"

#include "Gargantua/Physics/ECSPhysicsComponents.hpp"

#include "Gargantua/Renderer/ECSRendererComponents.hpp"

#include "Gargantua/Input/ECSInputComponents.hpp"

#include "Gargantua/Time/TimeStep.hpp"

#include "Gargantua/MPL/TypeList.hpp"

#include <algorithm>


namespace Gargantua
{
	namespace Renderer
	{
		class ECSCameraSystem : public ECS::ECSBaseSystem
		{
		public:
			using RequiredComponents = MPL::TypeList<Physics::PositionComponent, OrthoCameraComponent>;


			template <typename T>
			void Execute(const Time::TimeStep& ts, ECS::ComponentManager<T>& comp_mng)
			{
				real_t t = (real_t)ts.GetInSec();
				std::ranges::for_each(entities_registered,
					[&](ECS::Entity e)
					{
						Physics::PositionComponent& p = comp_mng.Get<Physics::PositionComponent>(e);

						OrthoCameraComponent& c = comp_mng.Get<OrthoCameraComponent>(e);

						//Update the position with the net movement from input if present.
						if (comp_mng.Has<Input::MoveActionComponent>(e))
						{
							Input::MoveActionComponent& a = comp_mng.Get<Input::MoveActionComponent>(e);
							p.position += t * a.net;
						}
						
						/*Input::MoveActionComponent& a = comp_mng.Get<Input::MoveActionComponent>(e);
						p.position += t * a.net;*/
						/*
						Compute the projection view.The camera view could change if another
						system (for example the system that blocks the camera to an entity)
						change the position and orientation of the camera. 
						*/
						//TODO: add rotation
						Math::Mat4df view = Math::Transform3d::Translate(Math::Vec3df{ p.position, 0 });
						c.projection_view = c.projection * view.Inverse();
					}
				);
			}
		};
	} //namespace Renderer
} //namespace Gargantua