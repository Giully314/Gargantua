/*
* gargantua/physics/physics_system.ixx
* 
* PURPOSE:
* 
* CLASSES:
* 
* DESCRIPTION
* 
* TODO:
*	- component tag to check in O(1) if an entity is registered to a system.
* 
* USAGE:
*/

export module gargantua.physics.physics_system;

import gargantua.types;
import gargantua.ecs.ecs;
import gargantua.physics.physics_components;
import gargantua.physics.physics_functions;
import gargantua.time.time_step;


namespace gargantua::physics
{
	export 
	class PhysicsSystem : public Singleton<PhysicsSystem>
	{
	public:

		/*
		* Register all the physics components.
		*/
		auto Startup(ecs::ECSSystem& ecs_s = ecs::ECSSystem::Instance())
		{
			ecs_s.Register<PositionComponent>();
			ecs_s.Register<VelocityComponent>();
			ecs_s.Register<ForceComponent>();
			ecs_s.Register<MassComponent>();
		}


		/*
		* Attach Position, Velocity, Force, Mass components to the entity.
		*/
		auto Register(ecs::entity_t e, f32 mass, 
			ecs::ECSSystem& ecs_s = ecs::ECSSystem::Instance()) -> void
		{
			ecs_s.Emplace<PositionComponent>(e);
			ecs_s.Emplace<VelocityComponent>(e);
			ecs_s.Emplace<ForceComponent>(e);
			ecs_s.Emplace<MassComponent>(e, mass);
		}


		/*
		* Remove Position, Velocity, Force, Mass components from the entity.
		*/
		auto Unregister(ecs::entity_t e, ecs::ECSSystem& ecs_s = ecs::ECSSystem::Instance()) -> void
		{
			ecs_s.Erase<PositionComponent>(e);
			ecs_s.Erase<VelocityComponent>(e);
			ecs_s.Erase<ForceComponent>(e);
			ecs_s.Erase<MassComponent>(e);
		}
		

		/*
		* Run phisycs simulation.
		*/
		auto Run(const time::TimeStep& ts, ecs::ECSSystem& ecs_s = ecs::ECSSystem::Instance()) -> void
		{
			const f32 dt = static_cast<f32>(ts.GetInSec());
			UpdateVelocity upv{ dt };
			UpdatePosition upp{ dt };
			ecs_s.ForEach<ForceComponent, MassComponent, VelocityComponent>(upv);
			ecs_s.ForEach<PositionComponent, VelocityComponent>(upp);
		}
	};
} // namespace gargantua::physics
