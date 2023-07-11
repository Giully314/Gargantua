/*
* gargantua/physics/physics_components.ixx
* 
* PURPSOSE: Define physical properties of an entity with components.
*	
* CLASSES:
*	PositionComponent:	info about the position of an entity.
*	VelocityComponent:	info about the velocity of an entity.
*	ForceComponent:		info about the force applied on an entity.
*	MassComponent:		info about the mass of an entity.
*	
*	QuadComponent:		size of the quad.
*	CircleComponent:	
*	
*	RigidBodyComponent:		info about the rigid body (coeff of restituion, frictions).
*	QuadCollisionComponent: info about the collision between two quads.
* 
* 
* TODO:
*	- define coordinate system.
*	- define baricenter and other info related to shape.
* 
*/

export module gargantua.physics.physics_components;

import <vector>;
import <utility>;

import gargantua.types;
import gargantua.math.vec2d;
import gargantua.ecs.entity;

export namespace gargantua::physics
{
	enum class BodyType : u8
	{
		Static,		// The body is still, no impulse.
		Dynamic,	// The body can be moved when interacts with other bodies in the impulse resolution.
		Kinematics, // The body can be moved but doesn't interact with other bodies in the impulse resolution.
	};



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


	// Precondition: m > 0.
	struct MassComponent
	{
		MassComponent() = default;
		
		MassComponent(f32 m_)
		{
			if (m_ == 0.0f)
			{
				inv_m = 0.0f;
				m = 0.0f;
			}
			else
			{
				m = m_;
				inv_m = 1.0f / m;
			}
		}

		constexpr 
		auto SetMass(const f32 new_mass) -> void
		{
			m = new_mass;
			inv_m = 1.0f / new_mass;
		}

		constexpr
		auto InfiniteMass() -> void
		{
			inv_m = 0.0f;
			m = 0.0f;
		}

		// Mass is in kg.
		f32 m = 1.0f;
		f32 inv_m = 1.0f;
	};

	
	struct QuadComponent
	{
		QuadComponent() = default;

		QuadComponent(f32 width, f32 height) : size(width, height)
		{

		}

		QuadComponent(const math::Vec2df& size_) : size(size_)
		{

		}

		// width, height
		math::Vec2df size{1.0f, 1.0f};
	};


	struct CircleComponent
	{

	};



	struct RigidBodyComponent
	{
		RigidBodyComponent() = default;

		RigidBodyComponent(f32 static_friction_, f32 dynamic_friction_, f32 restituition_, BodyType type_) : 
			static_friction(static_friction_),
			dynamic_friction(dynamic_friction_),
			restituition(restituition_), type(type_)
		{

		}

		RigidBodyComponent(f32 static_friction_, f32 dynamic_friction_, f32 restituition_) :
			RigidBodyComponent(static_friction_, dynamic_friction_, restituition_, BodyType::Dynamic)
		{

		}


		f32 static_friction = 0.5f;
		f32 dynamic_friction = 0.1f;
		f32 restituition = 1.0f;
		BodyType type = BodyType::Dynamic;
	};


	struct CollisionInfoComponent
	{
		CollisionInfoComponent() = default;


		CollisionInfoComponent(const math::Vec2df normal_, f32 penetration_) : normal(normal_),
			penetration(penetration_)
		{

		}

		CollisionInfoComponent(const std::pair<math::Vec2df, f32>& info) :
			CollisionInfoComponent(info.first, info.second)
		{

		}


		math::Vec2df normal;
		f32 penetration = 0.0f;
	};

	struct QuadCollisionComponent
	{
		QuadCollisionComponent() = default;

		QuadCollisionComponent(std::vector<ecs::entity_t>&& ents) : entities_in_collision(ents)
		{

		}


		// These 2 vectors are aligned: info[0] are the info about collision with the entities_in_collision[0]
		std::vector<ecs::entity_t> entities_in_collision;
		std::vector<CollisionInfoComponent> collisions_info;
	};



} // namespace gargantua::physics