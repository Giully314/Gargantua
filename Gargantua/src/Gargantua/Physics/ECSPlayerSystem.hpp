#pragma once
/*
Gargantua/Physics/ECSPlayerSystem.hpp

PURPOSE: Translate the input to force.

CLASSES:
	ECSPlayerSystem: ecs system for translating input to force of an entity.

DESCRIPTION:
	This system take the vector net from the MoveActionComponent (see the file for further informations) and add it 
	to the force component.
*/



#include "Gargantua/ECS/Types.hpp"
#include "Gargantua/ECS/ECSBaseSystem.hpp"
#include "Gargantua/ECS/ComponentManager.hpp"

#include "Gargantua/Physics/ECSPhysicsComponents.hpp"

#include "Gargantua/Input/ECSInputComponents.hpp"

#include "Gargantua/Time/TimeStep.hpp"

#include "Gargantua/MPL/TypeList.hpp"

#include <algorithm>


namespace Gargantua
{
	namespace Physics
	{
		class ECSPlayerSystem : public ECS::ECSBaseSystem
		{

		public:
			using RequiredComponents = MPL::TypeList<Input::MoveActionComponent, ForceComponent>;


			template <typename T>
			void Execute(const Time::TimeStep& ts, ECS::ComponentManager<T>& component_mng)
			{
				real_t t = (real_t)ts.GetInSec();

				std::ranges::for_each(entities_registered,
					[&](ECS::Entity e)
					{
						Input::MoveActionComponent& i = component_mng.Get<Input::MoveActionComponent>(e);
						ForceComponent& f = component_mng.Get<ForceComponent>(e);

						f.net_force += i.net;
					}
				);
			}
		};
	} //namespace Physics
} //namespace Gargantua