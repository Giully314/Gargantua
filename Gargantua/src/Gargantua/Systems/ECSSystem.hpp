#pragma once
/*
Gargantua/Systems/ECSSystem.hpp


PURPOSE: Manage ECS.


CLASSES:
	ECSSystem: System that handles the components of the ecs.


DESCRIPTION:
	Like other systems, this is a glue code for handling the components of the ECS directory. I chose a compile-time 
	setting orientation instaed of a runtime (for example for registering component types) because i like templates and 
	i prefer to reduce the complexity and polymorphism of the "runtime" approach.
	The API is pretty straightforward, just wrapper for the underlying methods of the components of the ECS.
	The 3 "core" methods are Register, Unregister and Get. These methods will be dispatched at compile time based
	on the type (a component or a system) used.


USAGE:
	using ListOfComponents = TypeList<TransformComponent, VelocityComponent, AccelerationComponent>;
	using ListOfSystems = TypeList<NewtonianSystem>;
	ECSSystem<ListOfComponents, ListOfSystems> ecs_sys;

	ecs_sys.Register<TransformComponent>(entity, parameters);
	ecs_sys.Register<VelocityComponent>(entity, parameters);
	ecs_sys.Register<AccelerationComponent>(entity, parameters);
	
	ecs_sys.Register<NewtonianSystem>(entity);

	while (true) //game loop
	{
		...
		ecs_sys.Execute<NewtonianSystem>(timestep);
		...
	}


TODO:
	Implement basic functionalities like: 
		GetAll<TransformComponent, SpriteComponent>() get all the entities with these components; (useful?)
		Execute(); execute all the systems registered. Maybe pass a variadic to specify the order of execution?
		Register<TypeListOfComponent>(entity); pass a type list or a variadic to register multiple components.
*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Concepts/ECS.hpp"

#include "Gargantua/ECS/EntityManager.hpp"
#include "Gargantua/ECS/ComponentManager.hpp"
#include "Gargantua/ECS/SystemManager.hpp"


#include "Gargantua/Generators/SequentialNumberGenerator.hpp"

#include <utility>
#include <concepts>


namespace Gargantua
{
	namespace Systems
	{

		template <typename TListOfComponents, typename TListOfSystems,
			template <class T> typename TGenerator = Generators::SequentialNumberGenerator>
		class ECSSystem
		{
		public:
			using TypeListOfComponents = TListOfComponents;
			using TypeListOfSystems = TListOfSystems;



			//*********************************** ENTITY MANAGER ***************************************
			ECS::Entity Create()
			{
				return entity_mng.Create();
			}


			void Destroy(ECS::Entity e)
			{
				entity_mng.Destroy(e);
			}


			bool InUse(ECS::Entity e) const noexcept
			{
				return entity_mng.InUse(e);
			}
			//*********************************** ENTITY MANAGER ***************************************
			

			//*********************************** COMPONENT MANAGER ***************************************
			
			template <typename TComponent, typename ...Args>
				requires std::constructible_from<TComponent, Args...> && 
					MPL::IsPresentV<TypeListOfComponents, TComponent>
			TComponent& Register(ECS::Entity e, Args&& ...args)
			{
				return component_mng.Register<TComponent, Args...>(e, std::forward<Args>(args)...);
			}


			template <typename TComponent>
				requires MPL::IsPresentV<TypeListOfComponents, TComponent>
			void Unregister(ECS::Entity e)
			{
				component_mng.Unregister<TComponent>(e);
			}


			template <typename TComponent>
				requires MPL::IsPresentV<TypeListOfComponents, TComponent>
			bool Has(ECS::Entity e) const
			{
				return component_mng.Has<TComponent>(e);
			}


			template <typename TComponent>
				requires MPL::IsPresentV<TypeListOfComponents, TComponent>
			TComponent& Get(ECS::Entity e)
			{
				return component_mng.Get<TComponent>(e);
			}


			template <typename TComponent>
				requires MPL::IsPresentV<TypeListOfComponents, TComponent>
			const TComponent& Get(ECS::Entity e) const
			{
				return component_mng.Get<TComponent>(e);
			}

			//*********************************** COMPONENT MANAGER ***************************************

			//*********************************** SYSTEM MANAGER ******************************************
			
			template <Concepts::System TSystem>
			void Register(ECS::Entity e)
			{
				system_mng.Register<TSystem>(e);
			}


			template <Concepts::System TSystem>
			void Unregister(ECS::Entity e)
			{
				system_mng.Unregister<TSystem>(e);
			}


			template <Concepts::System TSystem>
			TSystem& Get()
			{
				return system_mng.Get<TSystem>();
			}


			template <Concepts::System TSystem>
			const TSystem& Get() const
			{
				return system_mng.Get<TSystem>();
			}


			template <Concepts::System TSystem>
			void Execute(const Time::TimeStep& ts)
			{
				system_mng.Execute<TSystem>(ts, component_mng);
			}


			//*********************************** SYSTEM MANAGER ******************************************

		private:
			ECS::EntityManager<TGenerator> entity_mng;
			ECS::ComponentManager<TListOfComponents> component_mng;
			ECS::SystemManager<TListOfSystems> system_mng;
		};
	} //namespace Systems
} //namespace Gargantua