#pragma once
/*
Gargantua/ECS/SystemManager.hpp


PURPOSE: Manages multiple systems.


CLASSES:
	SystemManager: manager for the systems passed using a TypeList.


DESCRIPTION:
	Like the ComponentManager, this class is used to access all the systems passed using a TypeList at compile time.
	A system is the logic block that acts on the components of the registered entities. A system must only satisfy
	the concept System and the implementation is totally independent.


USAGE:
	using Systems = TypeList<PhysicsSystem, AnimationSystem>;
	SystemManager<Systems> sys_mng;

	sys_mng.Register<PhysicsSystem>(entity); 

	sys_mng.Execute<PhysicsSystem>(timestep, component_mng); 

	sys_mng.Unregister<PhysicsSystem>(entity);
*/

#include "Gargantua/Types.hpp"

#include "Gargantua/ECS/Types.hpp"
#include "Gargantua/ECS/ComponentManager.hpp"

#include "Gargantua/MPL/TypeList.hpp"

#include "Gargantua/Concepts/ECS.hpp"

#include "Gargantua/Time/TimeStep.hpp"

#include <tuple>


namespace Gargantua
{
	namespace ECS
	{
		namespace ECSPredicate
		{
			//Really ugly, temporary solution.
			template <Concepts::System T>
			struct CheckSystem
			{
				static constexpr bool Value = true;
			};
		} //namespace ECSPredicate


		template <typename TSystems>
		requires MPL::CheckPredicateV<TSystems, ECSPredicate::CheckSystem>
		class SystemManager
		{
		public:
			template <Concepts::System TSystem>
			TSystem& Get()
			{
				return std::get<TSystem>(systems);
			}

			template <Concepts::System TSystem>
			const TSystem& Get() const
			{
				return std::get<TSystem>(systems);
			}


			template <Concepts::System TSystem>
			void Register(Entity e)
			{
				TSystem& system = Get<TSystem>();
				system.Register(e);
			}


			template <Concepts::System TSystem>
			void Unregister(Entity e)
			{
				TSystem& system = Get<TSystem>();
				system.Unregister(e);
			}


			template <Concepts::System TSystem, typename TComponents>
			void Execute(const Time::TimeStep& ts, ComponentManager<TComponents>& component_mng)
			{
				TSystem& system = Get<TSystem>();
				system.Execute(ts, component_mng);
			}

		private:
			using SystemsStorageType = MPL::RebindT<TSystems, std::tuple>;
			SystemsStorageType systems;
		};
	} //namespace ECS
} //namespace Gargantua