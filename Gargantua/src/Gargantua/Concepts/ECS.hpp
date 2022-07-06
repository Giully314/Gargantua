#pragma once
/*
Gargantua/Concepts/ECS.hpp

PURPOSE: Compile time checks for ECS.

CLASSES:
	System: concept for a system registered in the SystemManager.

DESCRIPTION:
	A system must allow to register/unregister an entity and to execute the logic on the components, 
	with a timestep. The components are retrieved using the component manager passed to the Execute method.
	What does mean Register/Unregister an entity to the system? It means that, when Execute is called, the system
	will iterate through all the entities registered (so the system has an internal datastructure to keep these
	registered entities) and retrieves the components needed and updates them.
*/

#include "Gargantua/Types.hpp"

#include "Gargantua/ECS/Types.hpp"
#include "Gargantua/ECS/ComponentManager.hpp"

#include "Gargantua/Time/TimeStep.hpp"

namespace Gargantua
{
	namespace Concepts
	{
		template <typename TSystem>
		concept System = requires (TSystem system, ECS::Entity e, const Time::TimeStep & ts,
			ECS::ComponentManager<void>& component_mng)
		{
			//typename TSystem::RequiredComponents;
			{system.Execute(ts, component_mng)};
			{system.Register(e)};
			{system.Unregister(e)};
		};
	} //namespace Concepts
} //namespace Gargantua