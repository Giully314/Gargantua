/*
* gargantua/physics/physics_system.cpp
*/

module;

#include <gargantua/log/logger_macro.hpp>

module gargantua.physics.physics_system;

import gargantua.log.log;

namespace gargantua::physics
{

	auto PhysicsSystem::Run(const time::TimeStep& ts, ecs::ECSSystem& ecs_s) -> void
	{
		const f32 dt = static_cast<f32>(ts.GetInSec());
		Dynamics dynamics{ dt };
		ApplyGravity grav;
		
		ecs_s.ForEach<ForceComponent, MassComponent>(grav);
		
		// The block update velocity/position and update angular vel/rotation can be 
		// executed in parallel because they are independent.
		ecs_s.ForEach<VelocityComponent, ForceComponent, MassComponent>(dynamics);
		ecs_s.ForEach<PositionComponent, VelocityComponent>(dynamics);
		
		ecs_s.ForEach<AngularVelocityComponent, TorqueComponent, MomentInertiaComponent>(dynamics);
		ecs_s.ForEach<RotationComponent, AngularVelocityComponent>(dynamics);

		
		DetectCollisions(ecs_s);
		ResolveCollisions(ecs_s);
	}



	auto PhysicsSystem::DetectCollisions(ecs::ECSSystem& ecs_s) -> void
	{
		// TODO: For now the check for collisions is O(n^2). This is only for basic physics 
		// and for tests. In the future i will write a better system, based on quad tree probably.
		auto g = ecs_s.Group<PositionComponent, QuadComponent>();
		auto v1 = g.View();
		for (auto e1 : v1)
		{
			auto v2 = g.View();

			const auto& p1 = ecs_s.Get<PositionComponent>(e1);
			const auto& q1 = ecs_s.Get<QuadComponent>(e1);
			std::vector<ecs::entity_t> entities_in_collision;


			for (auto e2 : v2)
			{
				// This is done to avoid double collision detection. If e1 collides with e2 than e2 collides
				// with e1. To avoid the double computation and storage of informations, we skip all the 
				// entities that come before e2.
				// Another thing that can be done, is to do the collision detection based on order;
				// if e1 < e2 do the collision. This can be done in this system because entities 
				// can be ordered based on their id.
				/*while (e1 != e2) [[unlikely]]
				{
					continue;
				}*/
				if (e1 <= e2)
				{
					continue;
				}

				const auto& p2 = ecs_s.Get<PositionComponent>(e2);
				const auto& q2 = ecs_s.Get<QuadComponent>(e2);

				bool test = CollisionDetection::CheckCollision(p1, q1, p2, q2);
				if (test)
				{
					entities_in_collision.emplace_back(e2);
				}
			}

			auto& qc = ecs_s.Get<QuadCollisionComponent>(e1);
			// Maybe it's better to always do the move and release the previous memory.
			if (entities_in_collision.size() != 0)
			{
				qc.entities_in_collision = std::move(entities_in_collision);
			}
			else
			{
				qc.entities_in_collision.clear();
			}
			qc.collisions_info.clear();
		}

		// Compute the normal and penetration depth for each collision
		auto info_coll_g = ecs_s.Group<PositionComponent, QuadComponent, QuadCollisionComponent>();
		auto info_v = info_coll_g.View();
		for (auto e1 : info_v)
		{
			auto& ec = ecs_s.Get<QuadCollisionComponent>(e1);
			const auto& p1 = ecs_s.Get<PositionComponent>(e1);
			const auto& q1 = ecs_s.Get<QuadComponent>(e1);

			for (auto e2 : ec.entities_in_collision)
			{
				GRG_CORE_DEBUG("{} collides with {}", e1, e2);
				const auto& p2 = ecs_s.Get<PositionComponent>(e2);
				const auto& q2 = ecs_s.Get<QuadComponent>(e2);
				const auto info = CollisionDetection::CollisionNormal(p1, q1, p2, q2);
				ec.collisions_info.emplace_back(info);
			}
			GRG_CORE_DEBUG("****************************\n");
		}
	}


	auto PhysicsSystem::ResolveCollisions(ecs::ECSSystem& ecs_s) -> void
	{
		auto resolve_coll_g = ecs_s.Group<PositionComponent, VelocityComponent, MassComponent,
			RigidBodyComponent, QuadCollisionComponent>();
		auto resolve_v = resolve_coll_g.View();
		for (auto e1 : resolve_v)
		{
			auto& p1 = ecs_s.Get<PositionComponent>(e1);
			auto& v1 = ecs_s.Get<VelocityComponent>(e1);
			auto& m1 = ecs_s.Get<MassComponent>(e1);
			auto& r1 = ecs_s.Get<RigidBodyComponent>(e1);
			const auto& ec = ecs_s.Get<QuadCollisionComponent>(e1);

			for (u32 i = 0; i < ec.entities_in_collision.size(); ++i)
			{
				const auto e2 = ec.entities_in_collision[i];
				auto& p2 = ecs_s.Get<PositionComponent>(e2);
				auto& v2 = ecs_s.Get<VelocityComponent>(e2);
				auto& m2 = ecs_s.Get<MassComponent>(e2);
				auto& r2 = ecs_s.Get<RigidBodyComponent>(e2);
				const auto& info = ec.collisions_info[i];

				CollisionResolution::Resolve(info, p1, v1, m1, r1, p2, v2, m2, r2);
			}
		}
	}


} // namespace gargantua::physics