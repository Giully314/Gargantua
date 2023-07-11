/*
* gargantua/physics/physics_functions.ixx
* 
* PURPOSE: Definition of physics functions.
* 
* CLASSES:
*	Dynamics: apply the equations of motion.
*	ApplyGravity: apply gravity to every object that has the ForceComponent.
*	CollisionDetection: detect collisions and compute info about them. 
*	CollisionResolver: resolve collisions and friction.
* 
* DESCRIPTION:
*	For more informations about the functions:
*	How to Create a Custom Physics Engine: https://gamedevelopment.tutsplus.com/series/how-to-create-a-custom-physics-engine--gamedev-12715
*	Building a Physics Engine with C++ and Simulating Machines: https://www.youtube.com/watch?v=TtgS-b191V0
* 
* TODO:
*	- A possible optimization to check for collisions is to build a quadtree 
*		(https://en.wikipedia.org/wiki/Quadtree)
* 
*/

export module gargantua.physics.physics_functions;

import <cmath>;
import <algorithm>;
import <utility>;

import gargantua.types;
import gargantua.physics.physics_components;
import gargantua.math.vec2d;

export namespace gargantua::physics
{

	struct Dynamics
	{
		Dynamics(const f32 dt_) : dt(dt_)
		{

		}
		

		/*
		* Update position using velocity.
		*/
		auto operator()(PositionComponent& p, const VelocityComponent& v) -> void
		{
			p.p += v.v * dt;
		}


		/*
		* Update velocity by first computing acceleration from mass and force.
		*/
		auto operator()(VelocityComponent& v, const ForceComponent& f, const MassComponent& m) -> void
		{
			v.v += f.f * m.inv_m * dt;
		}


		const f32 dt;
	};

	
	/*
	* Gravity is the first force applied. This function is also to reset the force before
	* applying the gravity.
	*/
	struct ApplyGravity
	{
		ApplyGravity() = default;
		
		ApplyGravity(const f32 gravity) : g(gravity)
		{

		}

		
		auto operator()(ForceComponent& f, const MassComponent& m) -> void
		{
			f.f = { 0.0f, g * m.m };
		}

		const f32 g = -9.81f;
	};


	struct CollisionDetection
	{
		[[nodiscard]]
		static
		auto CheckCollision(const PositionComponent& p1, const QuadComponent& q1,
			const PositionComponent& p2, const QuadComponent& q2) -> bool
		{
			// Check if they do not intersect in the x direction.
			if (p1.p.x + q1.size.x < p2.p.x || p1.p.x > p2.p.x + q2.size.x) return false;
			
			// Check if they do not intersect in the y direction.
			if (p1.p.y + q1.size.y < p2.p.y || p1.p.y > p2.p.y + q2.size.y) return false;
			
			// No separating axis found, there is at least one overlapping axis.
			return true;
		}


		// Return a pair where first is the normal of the collision, second is the penetration.
		[[nodiscard]]
		static 
		auto CollisionNormal(const PositionComponent& p1, const QuadComponent& q1,
			const PositionComponent& p2, const QuadComponent& q2) -> std::pair<math::Vec2df, f32>
		{
			// Vector from p1 to p2
			auto diff = p2.p - p1.p;
			
			f32 a_x_extent = q1.size.x / 2.0f;
			f32 b_x_extent = q2.size.x / 2.0f;

			f32 a_y_extent = q1.size.y / 2.0f;
			f32 b_y_extent = q2.size.y / 2.0f;

			// Compute overlap on x and y axis to check for least penetration axis.
			f32 x_overlap = a_x_extent + b_x_extent - std::abs(diff.x);
			f32 y_overlap = a_y_extent + b_y_extent - std::abs(diff.y);

			math::Vec2df normal;
			f32 penetration = 0.0f;

			if (x_overlap < y_overlap)
			{
				if (diff.x < 0.0f)
				{
					normal.x = -1.0;
				}
				else
				{
					normal.x = 1.0f;
				}

				penetration = x_overlap;
			}
			else
			{
				if (diff.y < 0.0f)
				{
					normal.y = -1.0;
				}
				else
				{
					normal.y = 1.0f;
				}
				penetration = y_overlap;
			}
			
			return { normal, penetration };
		}
	};


	struct CollisionResolution
	{
		static 
		auto Resolve(const CollisionInfoComponent& info, 
			PositionComponent& p1, VelocityComponent& v1, const MassComponent& m1, const RigidBodyComponent& b1,
			PositionComponent& p2, VelocityComponent& v2, const MassComponent& m2, const RigidBodyComponent& b2) -> void
		{
			auto rv = v2.v - v1.v;
			f32 vel_along_normal = rv.Dot(info.normal);

			// Velocities are separating (?)
			if (vel_along_normal > 0.0f)
			{
				return;
			}

			f32 e = std::min(b1.restituition, b2.restituition);
			f32 inv_m_sum = m1.inv_m + m2.inv_m;

			// Compute impulse scalar
			f32 j = -(1.0f + e) * vel_along_normal;
			j /= inv_m_sum;

			// Apply impulse
			auto impulse = j * info.normal;
			v1.v -= m1.inv_m * impulse;
			v2.v += m2.inv_m * impulse;


			
			// Resolve friction
			rv = v2.v - v1.v;
			auto tangent = rv - rv.Dot(info.normal) * info.normal;
			tangent.Normalize();

			f32 jt = -rv.Dot(tangent);
			jt /= inv_m_sum;

			f32 mu = (b1.static_friction + b2.static_friction) / 2.0f;
			math::Vec2df friction_impulse;

			// The body is still so we use the static friction coeff.
			if (std::abs(jt) < j * mu)
			{
				friction_impulse = jt * tangent;
			}
			else // The body is moving with enough energy so we use the dynamic friction coeff.
			{
				f32 dyn_fr = (b1.dynamic_friction + b2.dynamic_friction) / 2.0f;
				friction_impulse = -j * dyn_fr * tangent;
			}

			v1.v -= m1.inv_m * friction_impulse;
			v2.v += m2.inv_m * friction_impulse;


			// positional correction
			/*
			* I tested different values of percent and everything below 0.6 has problems due to single precision
			* floating point.
			*/
			const f32 percent = 0.6f; // from 0.2 to 0.8
			const f32 slop = 0.01f; // from 0.01 to 0.1
			auto correction = (std::max(info.penetration - slop, 0.0f) / inv_m_sum) * percent * info.normal;
			p1.p -= m1.inv_m * correction;
			p2.p += m2.inv_m * correction;
		}
	};


} // namespace gargantua::physics