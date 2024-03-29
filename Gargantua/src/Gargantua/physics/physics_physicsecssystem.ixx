/*
* gargantua/physics/physics_physicsecssystem.ixx
* 
* PURPOSE: Provide newtonian physics simulation.
* 
* CLASSES:
*	PhysicsSystem: singleton that manage the physics simulation.
* 
* DESCRIPTION
*	Right now the system is pretty basic. The equations of motion are solved using the semi implicit Euler.
*	The collision system checks between every pair of entities (so it's not optimal O(n^2)) and the resolution
*	works only with non-oriented rigid bodies.
* 
* TODO:
*	- Improve the collision detection.
*	- Implement collision resolution for oriented rigid bodies.
*	- Support for different shapes.
* 
* DOUBTS:
*	I think the collision detection and resolve must be done in the same step to be accurate. 
*	Even though dividing the steps could lead to better parallelization and division the results could be
*	wrong (or not really ""realistic""). For example if we have 3 entities that collide and we resolve 
*	the collision between e1 and e2, maybe the resolve of collision e2 and e3 is different because the 
*	informations about the position are not the same.
*
* USAGE:
*	auto& phys = PhysicsSystem::Instance();
*	phys.Register(my_entity);
*	
*	phys.Run(timestep, ecs);
*	
* 
*/

export module gargantua.physics.physics_ecs_system;

import <vector>;
import <utility>;

import gargantua.types;
import gargantua.ecs;
import gargantua.physics.ecs_components;
import gargantua.physics.ecs_functions;
import gargantua.time.time_step;
import gargantua.math.vector;


namespace gargantua::physics
{
	export class PhysicsECSSystem : private NonCopyable, NonMovable
	{
	public:

		[[nodiscard]]
		static
		auto Instance() -> PhysicsECSSystem&
		{
			static PhysicsECSSystem sys;
			return sys;
		}

		/*
		* Register all the physics components.
		*/
		auto Startup(ecs::ECSSystem& ecs_s)
		{
			ecs_s.Register<PositionComponent>();
			ecs_s.Register<VelocityComponent>();
			ecs_s.Register<ForceComponent>();
			ecs_s.Register<MassComponent>();
			
		/*	ecs_s.Register<RotationComponent>();
			ecs_s.Register<AngularVelocityComponent>();
			ecs_s.Register<TorqueComponent>();
			ecs_s.Register<MomentInertiaComponent>();*/

			ecs_s.Register<QuadComponent>();
			ecs_s.Register<QuadCollisionComponent>();
			ecs_s.Register<RigidBodyComponent>();
		}


		/*
		* Attach Position, Velocity, Force, Mass, RigidBody, QuadComponent, QuadCollision
		* to the entity.
		*/
		auto Register(const ecs::entity_t e, const f32 mass, /*const f32 inertia, */
			const math::Vec2df& size,
			ecs::ECSSystem& ecs_s) -> void
		{
			ecs_s.Emplace<PositionComponent>(e);
			ecs_s.Emplace<VelocityComponent>(e);
			ecs_s.Emplace<ForceComponent>(e);
			ecs_s.Emplace<MassComponent>(e, mass);

			/*ecs_s.Emplace<RotationComponent>(e);
			ecs_s.Emplace<AngularVelocityComponent>(e);
			ecs_s.Emplace<TorqueComponent>(e);
			ecs_s.Emplace<MomentInertiaComponent>(e, inertia);*/

			ecs_s.Emplace<QuadComponent>(e, size);
			ecs_s.Emplace<RigidBodyComponent>(e);
			ecs_s.Emplace<QuadCollisionComponent>(e);
		}


		/*
		* Remove Position, Velocity, Force, Mass, RigidBody, QuadComponent, QuadCollision 
		* from the entity.
		*/
		auto Unregister(const ecs::entity_t e, ecs::ECSSystem& ecs_s) -> void
		{
			ecs_s.Erase<PositionComponent>(e);
			ecs_s.Erase<VelocityComponent>(e);
			ecs_s.Erase<ForceComponent>(e);
			ecs_s.Erase<MassComponent>(e);

			/*ecs_s.Erase<RotationComponent>(e);
			ecs_s.Erase<AngularVelocityComponent>(e);
			ecs_s.Erase<TorqueComponent>(e);
			ecs_s.Erase<MomentInertiaComponent>(e);*/

			ecs_s.Erase<QuadComponent>(e);
			ecs_s.Erase<RigidBodyComponent>(e);
			ecs_s.Erase<QuadCollisionComponent>(e);
		}
		

		/*
		* Run physics simulation.
		* 1) Apply gravity.
		* 2) Update velocity based on acceleration.
		* 3) Update position.
		* 4) Detect collisions.
		* 5) Resolve collisions.
		*/
		auto Run(const time::TimeStep& ts, ecs::ECSSystem& ecs_s) -> void;
	
	
	private:
		PhysicsECSSystem() = default;

		auto DetectCollisions(ecs::ECSSystem& ecs_s) -> void;
		auto ResolveCollisions(ecs::ECSSystem& ecs_s) -> void;
	};
} // namespace gargantua::physics
