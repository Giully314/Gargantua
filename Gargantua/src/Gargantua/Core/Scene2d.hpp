#pragma once
/*
Gargantua/Core/Scene2d.hpp

PURPOSE: information about the scene.

CLASSES:
	Scene2d: handle the current 2d scene.

DESCRIPTION:
	A scene is the place where the game "happens". It contains all the entities registered in the game and 
	manage the execution of the various steps to perform a tick of the simulation in the correct order.
	The functions related to entities forward the the calls to the underlying ecs system.
	There are some functions for the creation of the entities to make it easy to register an entity to a specific
	system with the corresponding components. 


TODO:
	Allow to register game states.
	Add the possibility to reset the scene. (maybe after the implementation of the scene serializer).
	Add the possilibity to execute only one step of the simulation.
	Add events inside the game and the API for these.
*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Systems/ECSSystem.hpp"
#include "Gargantua/Systems/EventSystem.hpp"

#include "Gargantua/ECS/Types.hpp"

#include "Gargantua/Time/TimeStep.hpp"

#include <utility>

namespace Gargantua
{
	namespace Core
	{
		class Scene2d
		{
		public:
			Scene2d() : camera(0)
			{
				ecs = CreateSharedRes<Systems::ECSSystem>();
			}
		
		
			void SetRenderer2d(SharedRes<Systems::Renderer2dSystem> r2d)
			{
				ecs->Get<Renderer::ECSRendererSystem>().SetRenderer2d(r2d);
			}


			void SetCamera(ECS::Entity camera)
			{
				this->camera = camera;
			}


			//************************* ENTITY CREATION ************************************

			ECS::Entity CreateEntity()
			{
				return ecs->Create();
			}

			void DestroyEntity(ECS::Entity e)
			{
				ecs->Destroy(e);
			}

			bool IsEntityAlive(ECS::Entity e)
			{
				return ecs->InUse(e);
			}

			//************************* ENTITY CREATION ************************************


			//************************* ENTITY COMPONENT ************************
			
			template <typename T>
			T& AssignComponent(ECS::Entity e)
			{
				return ecs->Register<T>(e);
			}

			template <typename T, typename ...Args>
			T& AssignComponent(ECS::Entity e, Args&& ...args)
			{
				return ecs->Register<T>(e, std::forward<Args>(args)...);
			}


			template <typename T>
			void RemoveComponent(ECS::Entity e)
			{
				return ecs->Unregister<T>(e);
			}


			template <typename T>
			T& GetComponent(ECS::Entity e)
			{
				return ecs->Get<T>(e);
			}


			template <typename T>
			bool HasComponent(ECS::Entity e)
			{
				return ecs->Has<T>(e);
			}

			//************************* ENTITY COMPONENT ************************


			//************************** ENTITIES AND SYSTEMS ********************************
			
			template <typename T>
			void RegisterEntityToSystem(ECS::Entity e)
			{
				ecs->Register<T>(e);
			}

			template <typename T>
			void UnregisterEntityFromSystem(ECS::Entity e)
			{
				ecs->Unregister<T>(e);
			}
			
			//************************** ENTITIES AND SYSTEMS ********************************



			//************************** ENTITY CREATION UTILITIES ***************************
			void CreateMotionEntity(ECS::Entity e); //register the motion components
			void CreateCollisionEntity(ECS::Entity e); //register the collision components
			
			void CreateInputActionEntity(ECS::Entity e); //register the input components

			void CreateOrthoCamera(ECS::Entity e); //register camera

			void CreateRendererEntity(ECS::Entity e); //register all the renderer components
		

			void CreatePlayerEntity(ECS::Entity e); //register physics, input, renderer
			

			//************************** ENTITY CREATION UTILITIES ***************************




			//************************** EXECUTE SIMULATION ********************************
			void RunScene(const Time::TimeStep& ts);
			//************************** EXECUTE SIMULATION ********************************


		private:
			//Current camera used to see the 2d scene.
			ECS::Entity camera;


			SharedRes<Systems::ECSSystem> ecs;
			//SharedRes<Systems::EventSystem> scene_events;
		};
	} //namespace Core
} //namespace Gargantua