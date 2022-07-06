#pragma once
/*
Gargantua/Physics/ECSGravitySystem.hpp


PURPOSE: Apply gravity.

CLASSES:
	ECSGravitySystem: ecs system for gravity.


DESCRIPTION:	
	Apply the force of gravity vector to every entity registered in this system. It just sum the gravity to the 
	net force of the entity.
*/


#include "Gargantua/ECS/Types.hpp"
#include "Gargantua/ECS/ECSBaseSystem.hpp"
#include "Gargantua/ECS/ComponentManager.hpp"

#include "Gargantua/Physics/ECSPhysicsComponents.hpp"

#include "Gargantua/Time/TimeStep.hpp"

#include "Gargantua/MPL/TypeList.hpp"

#include <algorithm>


namespace Gargantua
{
	namespace Physics
	{
		class ECSGravitySystem : public ECS::ECSBaseSystem
		{
		public:
			using RequiredComponents = MPL::TypeList<ForceComponent>;

			template <typename T>
			void Execute(const Time::TimeStep& ts, ECS::ComponentManager<T>& component_mng)
			{
				std::ranges::for_each(entities_registered,
					[&](ECS::Entity e)
					{
						ForceComponent& f = component_mng.Get<ForceComponent>(e);
						
						f.net_force += gravity_force;
					}
				);
			}


			void SetGravity(Math::Vec2df gravity)
			{
				gravity_force = std::move(gravity);
			}

		private:
			Math::Vec2df gravity_force{ 0.0f, -10.0f };
		};
	} //namespace Physics
} //namespace Gargantua
