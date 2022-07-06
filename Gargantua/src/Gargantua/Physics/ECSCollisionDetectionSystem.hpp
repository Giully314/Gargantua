#pragma once
/*
Gargantua/Physics/ECSCollisionDetectionSystem.hpp

PURPOSE: Detect collision.

CLASSES:
	ECSCollisionDetectionSystem: ecs system for detecting collision between entitites.

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
#include "Gargantua/Physics/ReferenceFrame.hpp"

#include "Gargantua/Math/MathFunctions.hpp"

#include "Gargantua/MPL/TypeList.hpp"

#include <algorithm>

#include <cmath>


namespace Gargantua
{
	namespace Physics
	{
		class ECSCollisionDetectionSystem : public ECS::ECSBaseSystem
		{
		public:
			using RequiredComponents = MPL::TypeList< PositionComponent, ScaleComponent, QuadShapeComponent,
				CollisionDetectionComponent>;

			template <typename T>
			void Execute(const Time::TimeStep& ts, ECS::ComponentManager<T>& component_mng)
			{
				for (auto it = entities_registered.begin(); it != entities_registered.end(); ++it)
				{
					ECS::Entity e1 = *it;

					PositionComponent& position1 = component_mng.Get<PositionComponent>(e1);
					ScaleComponent& scale1 = component_mng.Get<ScaleComponent>(e1);
					QuadShapeComponent & local_box1 = component_mng.Get<QuadShapeComponent>(e1);

					QuadShapeComponent world_box1;
					world_box1.min = Math::Product::Hadamard(local_box1.min, scale1.scale) + position1.position;
					world_box1.max = Math::Product::Hadamard(local_box1.max, scale1.scale) + position1.position;

					CollisionDetectionComponent& collision_component = component_mng.Get<CollisionDetectionComponent>(e1);

					std::for_each(it + 1, entities_registered.end(),
						[&](ECS::Entity e2)
						{
							auto& position2 = component_mng.Get<PositionComponent>(e2);
							ScaleComponent& scale2 = component_mng.Get<ScaleComponent>(e2);
							auto& local_box2 = component_mng.Get<QuadShapeComponent>(e2);

							QuadShapeComponent world_box2;
							world_box2.min = Math::Product::Hadamard(local_box2.min, scale2.scale) + position2.position;
							world_box2.max = Math::Product::Hadamard(local_box2.max, scale2.scale) + position2.position;


							if (TestAABBvsAABB(position1, world_box1, position2, world_box2, collision_component))
							{
								//register an event of collision maybe? 
								collision_component.entities_in_collision.push_back(e2);
							}
						}
					);
				}
			}


		private:
			bool TestAABBvsAABB(const PositionComponent& pa, const QuadShapeComponent& a,
				const PositionComponent& pb, const QuadShapeComponent& b, CollisionDetectionComponent& ca);
		};
	} //namespace Physics
} //namespace Gargantua

