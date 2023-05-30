/*
* gargantua/physics/physics_components.ixx
* 
* PURPSOSE:
* 
* CLASSES:
* 
* DESCRIPTION:
* 
* TODO:
* 
* USAGE:
*/

export module gargantua.physics.physics_components;

import gargantua.types;
import gargantua.math.vec2d;

export namespace gargantua::physics
{
	struct Position
	{
		Position() = default;
		Position(const math::Vec2df& position) : p(position)
		{

		}

		math::Vec2df p;
	};

	struct Velocity
	{
		Velocity() = default;
		Velocity(const math::Vec2df& velocity) : v(velocity)
		{

		}

		math::Vec2df v;
	};

	struct Acceleration
	{
		Acceleration() = default;
		Acceleration(const math::Vec2df& acceleration) : a(acceleration)
		{

		}

		math::Vec2df a;
	};

	struct Force
	{
		Force() = default;
		Force(const math::Vec2df& force) : f(force)
		{

		}

		math::Vec2df f;
	};

	struct Mass
	{
		Mass() = default;
		// Check for m != 0?
		Mass(f32 m) : inv_m(1.0f / m)
		{

		}

		// Inverse of mass, for faster computation of acceleration.
		f32 inv_m;
	};

} // namespace gargantua::physics