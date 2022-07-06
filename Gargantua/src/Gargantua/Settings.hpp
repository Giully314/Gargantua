#pragma once
/*
Gargantua/Settings.hpp


PURPOSE: Settings for ECS.


*/


#include "Gargantua/MPL/TypeList.hpp"


#include "Gargantua/Physics/ECSPhysicsComponents.hpp"
#include "Gargantua/Physics/ECSGravitySystem.hpp"
#include "Gargantua/Physics/ECSMotionSystem.hpp"
#include "Gargantua/Physics/ECSCollisionDetectionSystem.hpp"
#include "Gargantua/Physics/ECSCollisionResolverSystem.hpp"
#include "Gargantua/Physics/ECSPlayerSystem.hpp"

#include "Gargantua/Renderer/ECSRendererComponents.hpp"
#include "Gargantua/Renderer/ECSRendererSystem.hpp"
#include "Gargantua/Renderer/ECSCameraSystem.hpp"

#include "Gargantua/Input/ECSInputComponents.hpp"
#include "Gargantua/Input/ECSInputActionSystem.hpp"

#include "Gargantua/Generators/SequentialNumberGenerator.hpp"

namespace Gargantua
{
	using ListOfComponents = MPL::TypeList <
		Physics::PositionComponent, Physics::VelocityComponent, Physics::AccelerationComponent, 
		Physics::MassComponent, Physics::ForceComponent, 
		Physics::QuadShapeComponent, Physics::ScaleComponent,
		Physics::CollisionDetectionComponent,
		Physics::CoefficientRestituitionComponent,
		Physics::FrictionComponent,
	
		Renderer::TransformComponent,
		Renderer::ColorComponent,
		Renderer::OrthoCameraComponent,
	
		Input::MoveActionComponent>;


	using ListOfSystems = MPL::TypeList<
		Physics::ECSGravitySystem, Physics::ECSMotionSystem, 
		Physics::ECSCollisionDetectionSystem, Physics::ECSCollisionResolverSystem,
		Physics::ECSPlayerSystem,

		Renderer::ECSRendererSystem, Renderer::ECSCameraSystem,
	
		Input::ECSInputActionSystem>;

	template <typename T>
	using EntityNumberGenerator = Generators::SequentialNumberGenerator<T>;
} //namespace Gargantua