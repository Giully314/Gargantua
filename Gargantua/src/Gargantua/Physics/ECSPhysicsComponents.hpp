#pragma once
/*
Gargantua/Physics/ECSPhysicsComponents.hpp

PURPOSE: physics properties of an entity.

CLASSES:
	PositionComponent: position of the entity.
	VelocityComponent: velocity of the entity.
	AccelerationComponent: acceleration of the entity.
	MassComponent: inverse mass of the entity.
	ForceComponent: net force on the entity.

	CollisionDetectionComponent: informations about the collision with other entities.
	CoefficientRestituitionComponent: coefficient for collision.
	FrictionComponent: coeffiecients for friction.
	
	ScaleComponent: scale of the shape of the entity.
	QuadShapeComponent: shape of the entity.

DESCRIPTION:
	These components describe an entity in the physics world. 

TODO:
	add rotation components.
*/

#include "Gargantua/Types.hpp"

#include "Gargantua/ECS/Types.hpp"

#include "Gargantua/Math/Vec2d.hpp"

#include <vector>


namespace Gargantua
{
	namespace Physics
	{

		struct PositionComponent
		{
			Math::Vec2df position; //center of mass
		};


		struct VelocityComponent
		{
			Math::Vec2df velocity;
		};


		struct AccelerationComponent
		{
			Math::Vec2df acceleration;
		};


		struct MassComponent
		{
			real_t inv_mass = 0.0f; // inv_mass = 0.0f means an infinite mass.
		};


		struct ForceComponent
		{
			//Net force on the entity.
			Math::Vec2df net_force;
		};



		struct CollisionDetectionComponent
		{
			std::vector<ECS::Entity> entities_in_collision;
			std::vector<Math::Vec2df> normals; //direction of collision
			std::vector<real_t> penetration_depths; //used for positional correction
		};


		struct CoefficientRestituitionComponent
		{
			real_t e = 1.0f;
		};



		struct FrictionComponent
		{
			real_t static_friction = 1.0f;
			real_t dynamic_friction = 1.0f;
		};


		//*************************** SHAPES ********************************************************
		
		struct ScaleComponent
		{
			//Scale the width and height of the quad shape component.
			Math::Vec2df scale{1.0f, 1.0f};
		};


		struct QuadShapeComponent
		{
			Math::Vec2df min{-0.5f, -0.5f};
			Math::Vec2df max{0.5f, 0.5f};
		};

		

		//*************************** SHAPES ********************************************************


	} //namespace Physics
} //namespace Gargantua

