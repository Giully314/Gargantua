/*
* gargantua/physics/physics_components.ixx
* 
* PURPSOSE: Define physical properties of an entity with components.
*	
* CLASSES:
*	PositionComponent:	
*	VelocityComponent:	
*	ForceComponent:	
*	MassComponent:	
*	
	QuadComponent:	
*	CircleComponent:	
* 
* 
* DESCRIPTION:
* 
* TODO:
*	- defines coordinate system.
*	- defines baricenter and other info related to shape.
* 
* USAGE:
*/

export module gargantua.physics.physics_components;

import gargantua.types;
import gargantua.math.vec2d;

export namespace gargantua::physics
{
	// Position refers to baricenter? 
	struct PositionComponent
	{
		PositionComponent() = default;
		PositionComponent(const math::Vec2df& position) : p(position)
		{

		}

		math::Vec2df p;
	};

	struct VelocityComponent
	{
		VelocityComponent() = default;
		VelocityComponent(const math::Vec2df& velocity) : v(velocity)
		{

		}

		math::Vec2df v;
	};

	struct AccelerationComponent
	{
		AccelerationComponent() = default;
		AccelerationComponent(const math::Vec2df& acceleration) : a(acceleration)
		{

		}

		math::Vec2df a;
	};

	struct ForceComponent
	{
		ForceComponent() = default;
		ForceComponent(const math::Vec2df& force) : f(force)
		{

		}

		math::Vec2df f;
	};

	struct MassComponent
	{
		MassComponent() = default;
		// Check for m != 0?
		MassComponent(f32 m) : inv_m(1.0f / m)
		{

		}

		// Inverse of mass, for faster computation of acceleration.
		f32 inv_m;
	};

	//****************** SHAPES *************************************

	struct QuadComponent
	{
		// width, height
		math::Vec2df size;
	};


	struct CircleComponent
	{

	};

	//****************** SHAPES *************************************


} // namespace gargantua::physics