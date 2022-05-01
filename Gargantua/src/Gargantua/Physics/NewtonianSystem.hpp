#pragma once
/*
Gargantua/Physics/NewtonianSystem.hpp

PURPOSE: TEMPORARY SYSTEM FOR TESTING THE ECSSystem.



*/


#include "Gargantua/ECS/Types.hpp"
#include "Gargantua/ECS/ComponentManager.hpp"

#include "Gargantua/MPL/TypeList.hpp"

#include "Gargantua/Time/TimeStep.hpp"

#include "Gargantua/Physics/PhysicsComponents.hpp"

namespace Gargantua
{
	namespace Physics
	{
		class NewtonianSystem
		{
		public:
			//using NecessaryComponents = MPL::TypeList<TransformComponent>;

			template <typename T>
			void Execute(const Time::TimeStep& ts, ECS::ComponentManager<T>& component_mng)
			{

			}


			void Register(ECS::Entity e)
			{

			}


			void Unregister(ECS::Entity e)
			{

			}
		};

	} //namespace Physics
} //namespace Gargantua