/*
Gargantua/Core/Scene2d.cpp

DESCRIPTION:
	The only relevant function implmenation is RunScene. The other functions are straightforward.
	RunScene execute the various ecs systems in a specific order: 
		-Execute the input system for updating the input component that associate input to an "action vector".
		-Then run the physics simulation with first updating the player based on input and then gravity,
			motion, collision detection and collision resolving (temporary order fot these last 3).
		-Update the camera and set the camera for the renderer2d system.
		-Render all.
*/
#include "Scene2d.hpp"

#include "Gargantua/Settings.hpp"

namespace Gargantua
{
	namespace Core
	{
		void Scene2d::RunScene(const Time::TimeStep& ts)
		{
			//Execute input system
			ecs->Execute<Input::ECSInputActionSystem>(ts);


			//Execute physics systems 
			ecs->Execute<Physics::ECSPlayerSystem>(ts);
			ecs->Execute<Physics::ECSGravitySystem>(ts);
			ecs->Execute<Physics::ECSMotionSystem>(ts);
			ecs->Execute<Physics::ECSCollisionDetectionSystem>(ts);
			ecs->Execute<Physics::ECSCollisionResolverSystem>(ts);


			//Set up the rendering system and execute
			ecs->Execute<Renderer::ECSCameraSystem>(ts);

			ecs->Get<Renderer::ECSRendererSystem>().SetCamera(camera);
			ecs->Execute<Renderer::ECSRendererSystem>(ts);
		}



		void Scene2d::CreateMotionEntity(ECS::Entity e)
		{
			ecs->Register<Physics::PositionComponent>(e);
			ecs->Register<Physics::VelocityComponent>(e);
			ecs->Register<Physics::AccelerationComponent>(e);
			ecs->Register<Physics::MassComponent>(e);
			ecs->Register<Physics::ForceComponent>(e);
			ecs->Register<Physics::ECSMotionSystem>(e);
			ecs->Register<Physics::ECSGravitySystem>(e);
		}

		void Scene2d::CreateCollisionEntity(ECS::Entity e)
		{
			ecs->Register<Physics::QuadShapeComponent>(e);
			ecs->Register<Physics::ScaleComponent>(e);
			ecs->Register<Physics::CoefficientRestituitionComponent>(e);
			ecs->Register<Physics::FrictionComponent>(e);
			ecs->Register<Physics::CollisionDetectionComponent>(e);
			ecs->Register<Physics::ECSCollisionDetectionSystem>(e);
			ecs->Register<Physics::ECSCollisionResolverSystem>(e);
		}


		void Scene2d::CreateInputActionEntity(ECS::Entity e)
		{
			ecs->Register<Input::MoveActionComponent>(e);
			ecs->Register<Input::ECSInputActionSystem>(e);
		}


		void Scene2d::CreateOrthoCamera(ECS::Entity e)
		{
			ecs->Register<Physics::PositionComponent>(e);
			ecs->Register<Renderer::OrthoCameraComponent>(e);
			ecs->Register<Renderer::ECSCameraSystem>(e);
		}


		void Scene2d::CreateRendererEntity(ECS::Entity e)
		{
			ecs->Register<Renderer::TransformComponent>(e);
			ecs->Register<Renderer::ColorComponent>(e);
			ecs->Register<Renderer::ECSRendererSystem>(e);
		}


		void Scene2d::CreatePlayerEntity(ECS::Entity e)
		{
			CreateMotionEntity(e);
			CreateCollisionEntity(e);
			CreateInputActionEntity(e);
			CreateRendererEntity(e);

			ecs->Register<Physics::ECSPlayerSystem>(e);
		}
	} //namespace Core
} //namespace Gargantua