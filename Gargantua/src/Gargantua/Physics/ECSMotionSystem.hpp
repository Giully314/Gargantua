#pragma once
/*
Gargantua/Physics/ECSMotionSystem.hpp


PURPOSE: Implement motion for entities.


CLASSES:
	ECSMotionSystem: ecs system for motion.


DESCRIPTION:
	Basic motion implementation using Newton's equations and Euler semi-implicit integration method.

*/


#include "Gargantua/ECS/Types.hpp"
#include "Gargantua/ECS/ECSBaseSystem.hpp"
#include "Gargantua/ECS/ComponentManager.hpp"

#include "Gargantua/Physics/ECSPhysicsComponents.hpp"

#include "Gargantua/Time/TimeStep.hpp"


#include <algorithm>


namespace Gargantua
{
	namespace Physics
	{
		class ECSMotionSystem : public ECS::ECSBaseSystem
		{

		public:
			using RequiredComponents = MPL::TypeList< PositionComponent, VelocityComponent,
				AccelerationComponent, MassComponent, ForceComponent>;


			template <typename T>
			void Execute(const Time::TimeStep& ts, ECS::ComponentManager<T>& component_mng)
			{
				real_t t = (real_t)ts.GetInSec();
				
				std::ranges::for_each(entities_registered,
					[&](ECS::Entity e)
					{
						PositionComponent& p = component_mng.Get<PositionComponent>(e);
						VelocityComponent& v = component_mng.Get<VelocityComponent>(e);
						AccelerationComponent& a = component_mng.Get<AccelerationComponent>(e);
						MassComponent& m = component_mng.Get<MassComponent>(e);
						ForceComponent& f = component_mng.Get<ForceComponent>(e);


						a.acceleration = f.net_force * m.inv_mass;
						v.velocity += t * a.acceleration;
						p.position += t * v.velocity;


						f.net_force.Zero();
					}
				);
			}
		};
	} //namespace Physics
} //namespace Gargantua
