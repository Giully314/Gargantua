#pragma once
/*
Gargantua/Physics/ECSCollisionResolverSystem.hpp


PURPOSE: Resolve collisions.

CLASSES:
	ECSCollisionResolverSystem: ecs system for resolving collision between entities.

DESCRIPTION:
	This implementation is based on: https://gamedevelopment.tutsplus.com/series/how-to-create-a-custom-physics-engine--gamedev-12715.
	Check the articles for a better understanding.
*/

#include "Gargantua/Types.hpp"

#include "Gargantua/Core/EngineLogger.hpp"

#include "Gargantua/ECS/Types.hpp"
#include "Gargantua/ECS/ECSBaseSystem.hpp"
#include "Gargantua/ECS/ComponentManager.hpp"

#include "Gargantua/Time/TimeStep.hpp"

#include "Gargantua/Physics/ECSPhysicsComponents.hpp"

#include "Gargantua/MPL/TypeList.hpp"

#include <algorithm>



namespace Gargantua
{
	namespace Physics
	{
		class ECSCollisionResolverSystem : public ECS::ECSBaseSystem
		{
		public:
			using RequiredComponents = MPL::TypeList< CollisionDetectionComponent, VelocityComponent, MassComponent,
				CoefficientRestituitionComponent, PositionComponent, FrictionComponent>;

			template <typename T>
			void Execute(const Time::TimeStep& ts, ECS::ComponentManager<T>& component_mng)
			{
				//temporary
				real_t impulse_magnitude = 0.0f;

				std::ranges::for_each(entities_registered,
					[&](ECS::Entity entity_a)
					{
						CollisionDetectionComponent& cd = component_mng.Get<CollisionDetectionComponent>(entity_a);
						VelocityComponent& va = component_mng.Get<VelocityComponent>(entity_a);
						MassComponent& ma = component_mng.Get<MassComponent>(entity_a);
						CoefficientRestituitionComponent& cra = component_mng.Get<CoefficientRestituitionComponent>(entity_a);
						PositionComponent& pa = component_mng.Get<PositionComponent>(entity_a);
						FrictionComponent& fra = component_mng.Get<FrictionComponent>(entity_a);

						//iterate for every entity in collision registered inside the collision detection comp.
						//TODO: rewrite this loop using std or implement the zip function (like python).
						for (natural_t i = 0; i < cd.entities_in_collision.size(); ++i)
						{
							ECS::Entity entity_b = cd.entities_in_collision[i];

							VelocityComponent& vb = component_mng.Get<VelocityComponent>(entity_b);
							MassComponent& mb = component_mng.Get<MassComponent>(entity_b);
							CoefficientRestituitionComponent& crb = component_mng.Get<CoefficientRestituitionComponent>(entity_b);
							PositionComponent& pb = component_mng.Get<PositionComponent>(entity_b);
							FrictionComponent& frb = component_mng.Get<FrictionComponent>(entity_b);

							impulse_magnitude = ResolveCollision(va, ma, cra, vb, mb, crb, cd.normals[i], cd.penetration_depths[i]);
							
							if (impulse_magnitude != 0.0f)
								ResolveFriction(va, ma, fra, vb, mb, frb, cd.normals[i], impulse_magnitude);

							PositionalCorrection(pa, ma, pb, mb, cd.normals[i], cd.penetration_depths[i]);
						}


						cd.entities_in_collision.clear();
						cd.penetration_depths.clear();
						cd.normals.clear();
					}
				);
			}


		private:
			real_t ResolveCollision(VelocityComponent& va, const MassComponent& ma, const CoefficientRestituitionComponent& cra,
				VelocityComponent& vb, const MassComponent& mb, const CoefficientRestituitionComponent& crb,
				const Math::Vec2df& normal, const real_t penetration_depth);


			void ResolveFriction(VelocityComponent& va, const MassComponent& ma, const FrictionComponent& fra,
				VelocityComponent& vb, const MassComponent& mb, const FrictionComponent& frb,
				const Math::Vec2df& normal, const real_t impulse_magnitude);


			void PositionalCorrection(PositionComponent& pa, MassComponent& ma, 
				PositionComponent& pb, MassComponent& mb,
				const Math::Vec2df& normal, const real_t penetration_depth);
		};
	} //namespace Physics
} //namespace Gargantua