#pragma once
/*
Gargantua/Input/ECSInputActionSystem.hpp


PURPOSE: Convert the input into action.

CLASSES:
	ECSInputActionSystem: ecs system that transform the input into a vector representing an action.

DESCRIPTION:
	For now the only component is the component associated with movement. So the keys are checked and converted 
	into the net vector. This vector is then interpreted based on the entity type.
	For the camera entity is the velocity; for a player entity is a force summed to the net force.
*/


#include "Gargantua/ECS/Types.hpp"
#include "Gargantua/ECS/ECSBaseSystem.hpp"
#include "Gargantua/ECS/ComponentManager.hpp"

#include "Gargantua/Systems/InputSystem.hpp"

#include "Gargantua/Input/ECSInputComponents.hpp"

#include "Gargantua/Physics/ECSPhysicsComponents.hpp"

#include "Gargantua/Time/TimeStep.hpp"

#include "Gargantua/MPL/TypeList.hpp"

#include <algorithm>

namespace Gargantua
{
	namespace Input
	{
		class ECSInputActionSystem : public ECS::ECSBaseSystem
		{
		public:
			using RequiredComponents = MPL::TypeList<MoveActionComponent>;

			template <typename T>
			void Execute(const Time::TimeStep& ts, ECS::ComponentManager<T>& comp_mng)
			{
				std::ranges::for_each(entities_registered,
					[&](ECS::Entity e)
					{
						MoveActionComponent& a = comp_mng.Get<MoveActionComponent>(e);
						a.net.Zero();

						if (Systems::InputSystem::IsPressed(a.up.first))
						{
							a.net += a.up.second;
						}

						if (Systems::InputSystem::IsPressed(a.down.first))
						{
							a.net += a.down.second;
						}

						if (Systems::InputSystem::IsPressed(a.right.first))
						{
							a.net += a.right.second;
						}

						if (Systems::InputSystem::IsPressed(a.left.first))
						{
							a.net += a.left.second;
						}
					}
				);
			}
		};
	} //namespace Input
} //namespace Gargantua


