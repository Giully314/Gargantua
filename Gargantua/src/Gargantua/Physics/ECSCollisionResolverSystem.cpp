/*
Gargantua/Physics/ECSCollisionResolverSystem.cpp
*/
#include "ECSCollisionResolverSystem.hpp"



namespace Gargantua
{
	namespace Physics
	{
		real_t ECSCollisionResolverSystem::ResolveCollision(VelocityComponent& va, const MassComponent& ma, const CoefficientRestituitionComponent& cra,
			VelocityComponent& vb, const MassComponent& mb, const CoefficientRestituitionComponent& crb, 
			const Math::Vec2df& normal, const real_t penetration_depth)
		{
			//impulse section between the 2 entities that collide
			Math::Vec2df relative_velocity = vb.velocity - va.velocity;

			real_t velocity_along_normal = relative_velocity.Dot(normal);

			//Velocities are separiting, return.
			if (velocity_along_normal > 0)
			{
				return 0;
			}


			real_t e = std::min(cra.e, crb.e);

			//Calculate impulse scalar
			real_t j = -(1 + e) * velocity_along_normal;
			j /= (ma.inv_mass + mb.inv_mass);


			//Apply impulse to velocities
			Math::Vec2df impulse = j * normal;
			va.velocity -= ma.inv_mass * impulse;
			vb.velocity += mb.inv_mass * impulse;

			return j;
		}


		void ECSCollisionResolverSystem::ResolveFriction(VelocityComponent& va, const MassComponent& ma, const FrictionComponent& fra,
			VelocityComponent& vb, const MassComponent& mb, const FrictionComponent& frb,
			const Math::Vec2df& normal, const real_t impulse_magnitude)
		{
			Math::Vec2df relative_velocity = vb.velocity - va.velocity;

			Math::Vec2df tangent = relative_velocity - relative_velocity.Dot(normal) * normal;
			tangent.Normalize();

			//impulse along the tangent
			real_t jt = -relative_velocity.Dot(tangent);
			jt /= (ma.inv_mass + mb.inv_mass);

			real_t mu = (fra.static_friction + frb.static_friction) / 2.0f;

			Math::Vec2df friction_impulse;

			
			if (std::abs(jt) < impulse_magnitude * mu) //the body is basically stationary so we use the static coeff.
			{
				friction_impulse = jt * tangent;
			}
			else //the body is moving with enough energy so we use the dynamic coeff.
			{
				real_t dynamic_fr = (fra.dynamic_friction + frb.dynamic_friction) / 2.0f;
				friction_impulse = -impulse_magnitude * dynamic_fr * tangent;
			}

			va.velocity -= ma.inv_mass * friction_impulse;
			vb.velocity += mb.inv_mass * friction_impulse;
		}



		void ECSCollisionResolverSystem::PositionalCorrection(PositionComponent& pa, MassComponent& ma,
			PositionComponent& pb, MassComponent& mb,
			const Math::Vec2df& normal, const real_t penetration_depth)
		{
			const real_t percent = 0.2f;
			const real_t slop = 0.01f;
			Math::Vec2df correction = (std::max(penetration_depth - slop, 0.0f) / (ma.inv_mass + mb.inv_mass))
				* percent * normal;

			pa.position -= ma.inv_mass * correction;
			pb.position += mb.inv_mass * correction;
		}
	} //namespace Physics
} //namespace Gargantua