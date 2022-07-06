#pragma once
/*
Gargantua/ECS/ECSBaseSystem.hpp

PURPOSE: Base class for ecs systems.

CLASSES:
	ECSSystem: Provides basic functionality for Register/Unregister function in case of no specific requirements.

DESCRIPTION:
	If an ecs system doesn't need a specific functionality or data structure for Register/Unregister an entity, 
	this class implements, in a simple way, these methods using a std::vector.
*/

#include "Gargantua/ECS/Types.hpp"

#include <vector>
#include <algorithm>

namespace Gargantua
{
	namespace ECS
	{
		class ECSBaseSystem
		{
		public:
			void Register(ECS::Entity e)
			{
				entities_registered.push_back(e);
			}

			void Unregister(ECS::Entity e)
			{
				auto it = std::ranges::remove(entities_registered, e);
				entities_registered.erase(it.begin(), it.end());
			}

		protected:
			std::vector<ECS::Entity> entities_registered;
		};
	} //namespace ECS
} //namespace Gargantua